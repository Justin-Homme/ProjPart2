#ifndef PROC
#define PROC

/*
* Header file that makes a struct: Process with id, totalTime, remainingTime,
*   remainingCPU, remainingIO, priority, cpuBurst, ioBurst, state
*/
struct Process
{
  unsigned int id, totalTime, remainingTime, remainingCPU, remainingIO, real, user, sys, idle;
  int priority;
  unsigned short cpuBurst, ioBurst;
  char state;
};

/* creates a new process */
struct Process *createProcess(int newID, int priority, int cpuBurst,
  int ioBurst, int totalTime);

/* prints out the process */
void printProcess(struct Process *process);

/* prints out the timing stats of the process */
void printProcStats(struct Process *process);

/* switches current state to new state if legal transition */
int switchState(struct Process *processToSwitch, char newState);

#endif
