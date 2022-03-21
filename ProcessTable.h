#ifndef PROCTBL
#define PROCTBL

#include "Process.h"
/**
* struct with: numberProc, **processes, cpuProc, rr_slice
*
* functions: *createInitialTable, printTable, findpid, freeProcessTable
*/
struct ProcessTable
{
  int numberProc;
  struct Process **processes;
  int cpuProc;
  int rr_slice;
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
