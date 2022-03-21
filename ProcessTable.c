#include<stdio.h>
#include<stdlib.h>
#include "ProcessTable.h"

struct ProcessTable *createInitialTable(int newNumProcesses, int sliceval)
{
  struct ProcessTable *newTable = (struct ProcessTable *)malloc(sizeof(struct ProcessTable));

  newTable->numberProc = newNumProcesses;
  newTable->cpuProc = -1;
  newTable->rr_slice = sliceval;
  newTable->processes = (struct Process **)malloc(newNumProcesses * sizeof(struct Process*));

  return newTable;
}

void printTable(struct ProcessTable *tableToPrint)
{
  printf("Number of processes: %d\n", tableToPrint->numberProc);
  printf("ID\tPri\tCPU\tI/O\tTot\tRem\tState\n");
  
  for(int i = 0; i < tableToPrint->numberProc; i++)
  {
    printProcess(tableToPrint->processes[i]);
  }
}

int findpid(struct ProcessTable *tp, int pid)
{
  int count = 0;

  for(struct Process **curProc = tp->processes; curProc != NULL; curProc++)
  {
    struct Process *myCurProc = *curProc;
    int curPid = myCurProc->id;
    if(curPid == pid) {
      return count;
    } else {
      count++;
    }
  }
  return -1;
}

void freeProcessTable(struct ProcessTable *tableToFree)
{
  for(int i = 0; i < tableToFree->numberProc; i++)
  {
    free(tableToFree->processes[i]);
  }
  free(tableToFree);
}
