#include<stdio.h>
#include<sdtlib.h>
#include "Clock.h"

struct ProcessTable *myProcTable = (struct ProcessTable *) malloc(sizeof(struct ProcessTable));
remProcesses = myProcTable -> numberProc;   // all processes remain

clockTick()
{
    tick = 1;
    struct Process **myCurProc = myProcTable -> processes[0];

    while(remProcesses > 0) {
        printf("%04d: \n", tick);

        if(myCurProc -> remainingTime = 0) {
            switchState(myCurProc, 'T');
            printf("%04d: Process ID %d moved to T\n", tick, myCurProc -> id);
            myCurProc -> real = tick - 1;           // tick represents full time + 1
            printf("Process: %d\n real: %d\n user: %d\n sys: %d idle: %d\n",
                    myCurProc -> id, myCurProc -> real, myCurProc -> user,
                    myCurProc -> sys, myCurProc -> idle);
            remProcesses = remProcesses - 1;    // remaining processes decrement
        } else {
            switch(myCurProc -> curState) {
                case 'R':                       // check if it's in Running state
                    if(myCurProc -> remainingCPU = 0) {
                        switchState(myCurProc, 'B');
                        myCurProc -> remainingIO = myCurProc -> ioBurst;
                        printf("%04d: Process ID %d moved to B\n", tick, myCurProc -> id);
                    } else {
                        myCurProc -> remainingCPU = myCurProc -> remainingCPU - 1;
                        myCurProc -> user = myCurProc -> user + 1;  // user time increases
                        break;
                    }

                case 'B':                       // check if it's in Blocked state
                    if(myCurProc -> remainingIO = 0) {
                        switchState(myCurProc, 'Q');
                        myCurProc -> remainingCPU = myCurProc -> cpuBurst;
                        printf("%04d: Process ID %d moved to Q\n", tick, myCurProc -> id);
                    } else {
                        myCurProc -> remainingIO = myCurProc -> remainingIO - 1;
                        myCurProc -> sys = myCurProc -> sys + 1;    // system time increases
                        break;
                    }
            }

        }

        tick++;
        myCurProc -> remainingTime = myCurProc -> remainingTime -1;
    }

} // clocktick
