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
        printf("%04d: ", tick);
        if(myCurProc -> remainingTime = 0) {
            switchState(myCurProc, 'T');
            printf("%04d: Process ID %d moved to T", tick, myCurProc -> id);
        } else {
            switch(myCurProc -> curState) {
                case 'R':
                    if(myCurProc -> remainingCPU = 0) {
                        switchState(myCurProc, 'B');
                        myCurProc -> remainingIO = myCurProc -> ioBurst;
                        printf("%04d: Process ID %d moved to B", tick, myCurProc -> id);
                    }

                case 'B':
                    if(myCurProc -> remainingIO = 0) {
                        switchState(myCurProc, 'Q');
                        myCurProc -> remainingCPU = myCurProc -> cpuBurst;
                        printf("%04d: Process ID %d moved to Q", tick, myCurProc -> id);
                }
            }

        }

        tick++;
    }

} // clocktick
