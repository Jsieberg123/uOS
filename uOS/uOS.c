#include "uOS.h"
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect)
{
	for(int i=0;i<numberOfTasks;i++)
	{
		if(tasks[i].state == WAIT)
		{
			if(!(tasks[i].time--))
			{
				tasks[i].state = READY;
			}
		}
	}
}

int CreateTask(void (*func)(void*, int))
{
	tasks[numberOfTasks].time=0;
	tasks[numberOfTasks].state=DONE;
	tasks[numberOfTasks].priority=0;
	tasks[numberOfTasks].func = func;

	return numberOfTasks++;
}

void AddTask(int task, unsigned int time, void* param)
{
	tasks[task].time = time;
	tasks[task].state = WAIT;
	tasks[task].param = param;
}

void SetPriority(int task, unsigned char priority)
{
	tasks[task].priority = priority;
}

void Run()
{
	OCR1A = 800;
    TCCR1B = 0x09;
    TIMSK1 |= (1 << OCIE1A);

	sei();

	while(true)
	{
		unsigned int nextTask = chooseNextTask();
		runTask(nextTask);
	}
}

void runTask(int task)
{
	tasks[task].state == RUN;
	tasks[task].func(tasks[task].param, task);
	tasks[task].state == DONE;
}

int chooseNextTask()
{
	for(int i=PRIORITIES;i>=0;i--)//for each priority
	{
		for(int j=0;j<numberOfTasks;j++)//for each task
		{
			if(tasks[j].priority == i && tasks[j].state == READY)
			{
				return i;
			}
		}
	}
}

