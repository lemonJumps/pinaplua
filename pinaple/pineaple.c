#include "pineaple.h"

/*

how to work this thing:

before the vm starts, register global things, variables, prebuilt classes.
first put them into storage and then put their name into NameDB.

if possible functions should be their own VMs, but could be just jumps;
since the VM is literally just an I D and R stack. NOW the stacks can be interchanged on the fly/
so, simple optimizations are possible

*/