#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"

typedef struct Alarms Alarms;
struct Alarms
{
	QLock;
	Proc	*head;
};

static Alarms	alarms;
static Rendez	alarmr;

void
alarmkproc(void*)
{
	Proc *rp, **l;
	ulong now;

	procpriority(up, PriKproc, 1);
	for(;;){
		now = sys->ticks;
		qlock(&alarms);
		l = &alarms.head;
		while((rp = *l) != nil && tickscmp(now, rp->alarm) >= 0){
			if(canqlock(&rp->debug)){
				if(!waserror()){
					postnote(rp, 0, "alarm", NUser);
					poperror();
				}
				qunlock(&rp->debug);
				rp->alarm = 0;
				*l = rp->palarm;
			}else
				l = &rp->palarm;
		}
		qunlock(&alarms);

		sleep(&alarmr, return0, 0);
	}
}

/*
 *  called every clock tick
 */
void
checkalarms(void)
{
	Proc *p;

	p = alarms.head;
	if(p != nil && tickscmp(sys->ticks, p->alarm) >= 0)
		wakeup(&alarmr);
}

static void
disalarm(Proc *p)
{
	Proc **l, *f;

	qlock(&alarms);
	for(l = &alarms.head; (f = *l) != nil; l = &f->palarm){
		if(f == p){
			*l = f->palarm;
			f->palarm = nil;
			break;
		}
	}
	qunlock(&alarms);
}

ulong
procalarm(ulong time)
{
	Proc **l, *f;
	ulong when, old;

	old = up->alarm;
	if(up->alarm){
		disalarm(up);
		old = tk2ms(old - sys->ticks);
	}else
		old = 0;
	if(time == 0) {
		up->alarm = 0;
		return old;
	}
	when = ms2tk(time)+sys->ticks;
	if(when == 0)
		when = 1;

	qlock(&alarms);
	up->alarm = when;
	l = &alarms.head;
	while((f = *l) != nil && tickscmp(f->alarm, when) < 0)
		l = &f->palarm;
	up->palarm = *l;
	*l = up;
	qunlock(&alarms);

	return old;
}
