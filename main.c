#include <stdio.h>
#include "uOS.h"
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void Hello(void *unused, int me)
{
    printf("Hello World!\n");

    AddTask(me, 2500, NULL);
}

void Interupted(void *unused, int me)
{
	AddTask(me, 50000, NULL);
	for (unsigned long i=0; i < 800000; i++);
	printf("Here\n");
}

void Interupted2(void *unused, int me)
{
    printf("Started\n");
    while (true)
    {
		for (unsigned long i=0; i < 1600000; i++);
		printf("Here2\n");
    }
}

int main()
{
    cli();

    uart_init();
    stdout = &uart_output;
    stdin = &uart_input;

    int helloTask = CreateTask(Hello);
    int inter = CreateTask(Interupted);
    int inter2 = CreateTask(Interupted2);
    SetPriority(helloTask, 2);
    SetPriority(inter, 1);
    SetPriority(inter2, 0);

    AddTask(helloTask, 2, NULL);
    AddTask(inter, 2, NULL);
    AddTask(inter2, 2, NULL);

    printf("Starting\n");
    Run();
}