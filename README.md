# README #

Source for an experimental 64-bit Plan 9 kernel, and supporting software. It features a revised memory-management system, MCS spin locks, and other changes to system data structures to support full 64-bit addressing. Changes to the scheduler are also planned, to improve support for multicore. Currently it supports AMD64 (x86-64, Intel 64), although parts have run on other platforms. Use it together with https://code.google.com/p/plan9/ for the source of compilers, libraries and commands.

This fork of Plan 9's 64-bit 9k kernel is developed and maintained by charles.forsyth@gmail.com with many experimental changes compared to the original,
hence the name 9exp instead of 9k.
