#ifndef _CLOCK
#define _CLOCK

#include"ProcessTable.h"

struct Clock {
    struct ProcessTable *myProcTable;
    struct Process *myCurProc;
    int tick, remProcesses, rr_slice, remSlice, proc_index;
    char schedType;
};

struct Clock *createClock(struct ProcessTable *procTable, int slice, char schedType);

/* makes the clock tick and takes care of what happens when it does */
void clockTick(struct Clock *myClock);

/* uses schedType to choose next process */
struct Process *nextProc(struct Clock *myClock);

/* looks for highest priority task in myProcTable*/
//struct Process *findHighPri(struct ProcessTable *myProcTable);
struct Process *findHighPri(struct Clock *clock);

/* looks for process with shortest remaining time */
struct Process *findShortest(struct ProcessTable *myProcTable);

/* a function to free up to clock */
void freeClock(struct Clock *clockToFree);
#endif
