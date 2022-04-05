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
  }

} // clocktick
