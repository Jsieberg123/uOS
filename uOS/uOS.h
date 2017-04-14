#ifndef UOS_H_
#define UOS_H_

#include <stdbool.h>

#define MAX_TASKS 5
#define PRIORITIES 5

enum TASK_STATE {
    WAIT,
	READY,
	RUN,
	DONE
};

typedef enum TASK_STATE TASK_STATE;

struct TASK{
    unsigned long time;
	TASK_STATE state;
	unsigned char priority;
	void (*func)(void*, int);
	void* param;
};
typedef struct TASK Task;

volatile Task tasks[MAX_TASKS];

int CreateTask(void (*func)(void*, int));

void AddTask(int task, unsigned long time, void* param);

void SetPriority(int task, unsigned char priority);

void Run();

int chooseNextTask();

void runTask(int task);

#endif