#ifndef PROCTBL
#define PROCTBL

#include "Process.h"
/**
* struct with: numberProc, **processes, cpuProc, timeSlice, clockTime
*
* functions: *createInitialTable, printTable, findpid, freeProcessTable
*/
struct ProcessTable
{
  int numberProc;
  struct Process **processes;
  int cpuProc, timeSlice, clockTime;
// int rr_slice; // time slice for round robin scheduling
};

/** creates a ProcessTable with the provided data */
struct ProcessTable *createInitialTable(int newNumProcesses, int sliceval);

/** prints out process information */
void printTable(struct ProcessTable *tableToPrint);

/** return the index of the process with matching pid */
int findpid(struct ProcessTable *tp, int pid);

/** frees of all information created with malloc */
void freeProcessTable(struct ProcessTable *tableToFree);

#endif
