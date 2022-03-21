#ifndef PROC
#define PROC

/**
* Header file that makes a struct: Process
* with id, totalTime, remainingTime, priority, cpuBurst, ioBurst, state
*/
struct Process
{
  unsigned int id, totalTime, remainingTime;
  int priority;
  unsigned short cpuBurst, ioBurst;
  char state;
};

void printProcess(struct Process *process);

struct Process *createProcess(int newID, int priority, int cpuBurst,
  int ioBurst, int totalTime);

int switchState(struct Process *processToSwitch, char newState);

#endif
