#include<stdio.h>
#include<stdlib.h>
#include "Clock.h"

//struct ProcessTable myProcTable = (struct ProcessTable *) malloc(sizeof(struct ProcessTable));

struct Clock *createClock(struct ProcessTable *procTable, int slice, char schedType) {
        struct Clock *newClock = (struct Clock*) malloc(sizeof(struct Clock));
        newClock->myProcTable = procTable;
        newClock->myCurProc = findHighPri(newClock);
//        newClock->myCurProc = procTable->processes[0];
        newClock->tick = 1;
        newClock->remProcesses = procTable-> numberProc;    // all processes remain
        newClock->rr_slice = slice;
        newClock->remSlice = slice;                         // full slice on creation
        newClock->proc_index = 0;
        newClock->schedType = schedType;
}

void clockTick(struct Clock *myClock)
{

    //int tick = myClock->tick;

    while(myClock->tick < 50) {
        printf("%04d: \n", myClock->tick);

        if(myClock->myCurProc->remainingTime == 0) {
            if(myClock->myCurProc->state == 'T') {
                myClock->myCurProc = nextProc(myClock);
            } else {
                switchState(myClock->myCurProc, 'T');
                printf("%04d: Process ID %d moved to T\n", myClock->tick, myClock->myCurProc->id);
                myClock->myCurProc->real = myClock->tick - 1;           // tick represents full time + 1
                myClock->myCurProc->idle = myClock->myCurProc->real - (myClock->myCurProc->sys + myClock->myCurProc->user); // idle = total - (sys + user)
                printProcStats(myClock->myCurProc);
                myClock->myCurProc = nextProc(myClock);
                myClock->remProcesses = myClock->remProcesses - 1;    // remaining processes decrement
            }
        } else {
            switch(myClock->myCurProc->state) {
                case 'R':                       // check if it's in Running state
                    if(myClock->myCurProc->remainingCPU == 0) {
                        switchState(myClock->myCurProc, 'B');
                        myClock->myCurProc->remainingIO = myClock->myCurProc->ioBurst;
                        printf("%04d: Process ID %d moved to B\n", myClock->tick, myClock->myCurProc->id);
                        break;
                    } else {
                        myClock->myCurProc->remainingCPU = myClock->myCurProc->remainingCPU - 1;
                        myClock->remSlice = myClock->remSlice - 1;
                        myClock->myCurProc->sys = myClock->myCurProc->sys + 1;    // user time increases
                        if(myClock->schedType == 'R' && myClock->remSlice == 0) {     // for Round Robin
                            nextProc(myClock);
                        }
                        myClock->myCurProc->remainingTime = myClock->myCurProc->remainingTime -1;
                    }
                    break;

                case 'B':                       // check if it's in Blocked state
                    if(myClock->myCurProc->remainingIO == 0) {
                        switchState(myClock->myCurProc, 'Q');
                        myClock->myCurProc->remainingCPU = myClock->myCurProc->cpuBurst;
                        nextProc(myClock);
                        printf("%04d: Process ID %d moved to Q\n", myClock->tick, myClock->myCurProc->id);
                        break;

                    } else {
                        myClock->myCurProc->remainingIO = myClock->myCurProc->remainingIO - 1;
                        myClock->remSlice = myClock->remSlice - 1;
                        myClock->myCurProc->user = myClock->myCurProc->user + 1;    // user time increases
                        if(myClock->schedType == 'R' && myClock->remSlice == 0) {     // for Round Robin
                            nextProc(myClock);
                        }
                        myClock->myCurProc->remainingTime = myClock->myCurProc->remainingTime -1;
                    }
                    break;
                case 'N':
                    switchState(myClock->myCurProc, 'Q');
                    printf("%04d: Process ID %d moved to Q\n", myClock->tick, myClock->myCurProc->id);
                    switchState(myClock->myCurProc, 'R');
                    printf("%04d: Process ID %d moved to R\n", myClock->tick, myClock->myCurProc->id);
                    break;
                case 'Q':
                    //nextProc(myClock);
                    myClock->myCurProc = nextProc(myClock);
                    myClock->myCurProc->remainingTime = myClock->myCurProc->remainingTime -1;
                    break;
            }
        }
        myClock->tick = myClock->tick + 1;

    }

} // clocktick

struct Process *nextProc(struct Clock *myClock)
{
    struct Process *newProc;
    switch(myClock->schedType) {
        case 'R':
            myClock->remSlice = myClock->rr_slice;        // switching proc so reset remSlice
            newProc = findHighPri(myClock);
            break;
        case 'F':
            newProc = findHighPri(myClock);
            break;
        case 'S':
            newProc = findShortest(myClock->myProcTable);
            break;
        default:
            printf("Something went wrong...");
    }
    return newProc;
} // nextProc

struct Process *findHighPri(struct Clock *myClock)
{
    struct ProcessTable *procTable = myClock->myProcTable;
    struct Process *highestPriProc = procTable->processes[0];
    for(int i = 1; i < procTable->numberProc; i++) {
        struct Process *cur = myClock->myProcTable->processes[i];
        if(cur->priority < highestPriProc->priority) {
            if(cur->state != 'T') {       // skips over terminated processes
                highestPriProc = cur;
            }
        }
    }
    return highestPriProc;
} // findHighPri

struct Process *findShortest(struct ProcessTable *myProcTable)
{
    struct Process *shortestProc = myProcTable->processes[0];
    for(int i = 1; i < myProcTable->numberProc; i++) {
        struct Process *cur = myProcTable->processes[i];
        if(cur->remainingTime < shortestProc->remainingTime && cur->remainingTime > 0) {
            if(cur->state !='T') {
                shortestProc = cur;
            }
        }
    }
    return shortestProc;
} // findShortest

void freeClock(struct Clock *clockToFree)
{
    freeProcessTable(clockToFree->myProcTable);
    free(clockToFree);

} // freeClock
