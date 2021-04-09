# README #

Source for an experimental 64-bit Plan 9 kernel, and supporting software. It features a revised memory-management system, MCS spin locks, and other changes to system data structures to support full 64-bit addressing. Changes to the scheduler are also planned, to improve support for multicore. Currently it supports AMD64 (x86-64, Intel 64), although parts have run on other platforms. Use it together with https://code.google.com/p/plan9/ for the source of compilers, libraries and commands.

This version of 9k is developend and maintained by charles.forsyth@gmail.com with many experimental changes compared to the original.
Since that's now more generally available, this will probably get a new name to reduce confusion.
