#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void handle(int s)
{
	printf("��ʱ��ʱ�䵽!\n");
	exit(-1);
}
main()
{
	signal(SIGALRM,handle);
	alarm(5);
	while(1);
}
