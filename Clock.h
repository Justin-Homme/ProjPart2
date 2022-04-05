#ifndef _CLOCK
#define _CLOCK

#include"ProcessTable.h"

struct ProcessTable *myProcTable;

int tick, remProcesses;

/** makes the clock tick and takes care of what happens when it does */
clockTick();

#endif
