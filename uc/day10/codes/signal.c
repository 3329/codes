#include <signal.h>
#include <stdio.h>
#include <unistd.h>
void handle(int s)
{
	printf("�յ��ź�!\n");
} 
main()
{
	signal(2,handle);
	printf("pid=%d\n",getpid());
	while(1);
}
