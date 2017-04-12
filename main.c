#include <stdio.h>
#include "uOS.h"

void Hello(void* unused, int me)
{
	printf("Hello World!\n");

	AddTask(me, 2500);
}

int main()
{
	int helloTask = CreateTask(Hello);
	SetPriority(helloTask, 2);

	AddTask(helloTask, 0);

	Run();
}