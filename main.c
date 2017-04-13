#include <stdio.h>
#include "uOS/uOS.h"

void Hello(void* unused, int me)
{
	printf("Hello World!\n");

	AddTask(me, 2500, NULL);
}

int main()
{
	int helloTask = CreateTask(Hello);
	SetPriority(helloTask, 2);

	AddTask(helloTask, 0, NULL);

	Run();
}