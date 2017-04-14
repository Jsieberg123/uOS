#include "uOS.h"
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned int numberOfTasks = 0;
volatile int runningTaskId = 0;

ISR(TIMER1_COMPA_vect)
{
    for (int i = 0; i < numberOfTasks; i++)
    {
        if (tasks[i].state == WAIT)
        {
            if (!(tasks[i].time--))
            {
                tasks[i].state = READY;
            }
        }
        if (tasks[i].state == READY)
        {
            if (tasks[i].priority > tasks[runningTaskId].priority)
            {
                int lastTask = runningTaskId;
                TIFR1 &= ~(1 << OCF1A); //clear the interrupt flag
                runTask(i);
                runningTaskId = lastTask;
            }
        }
    }
}
int CreateTask(void (*func)(void *, int))
{
    tasks[numberOfTasks].time = 0;
    tasks[numberOfTasks].state = DONE;
    tasks[numberOfTasks].priority = 0;
    tasks[numberOfTasks].func = func;

    return numberOfTasks++;
}

void AddTask(int task, unsigned long time, void *param)
{
    tasks[task].time = time;
    tasks[task].state = WAIT;
    tasks[task].param = param;
}

void SetPriority(int task, unsigned char priority)
{
    if (tasks[task].state != RUN)
    {
        tasks[task].priority = priority;
    }
}

void Run()
{
    OCR1A = 800;
    TCCR1B = 0x09;
    TIMSK1 |= (1 << OCIE1A);

    sei();

    while (true)
    {
        int nextTask = chooseNextTask();
        if (nextTask != -1)
        {
            runTask(nextTask);
        }
    }
}

void runTask(int task)
{
    tasks[task].state == RUN;
    runningTaskId = task;
    tasks[task].func(tasks[task].param, task);
    tasks[task].state == DONE;
}

int chooseNextTask()
{
    for (int i = 0; i < numberOfTasks; i++) //for each task
    {
        if (tasks[i].state == READY)
        {
            return i;
        }
    }
    return -1;
}
