#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void handle(int s)
{
	printf("定时器时间到!\n");
	exit(-1);
}
main()
{
	signal(SIGALRM,handle);
	alarm(5);
	while(1);
}
