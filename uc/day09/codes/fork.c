#include <unistd.h>
#include <stdio.h>
main()
{
	printf("进程创建前!\n");
	pid_t pid=57575;
	pid=fork();
	if(pid==0){		
		while(1)
		{
			printf("子进程--1\n");
		}
	}
	if(pid)
	{		
		while(1)
		{
			printf("父进程------2\n");
		}
	}
	
}
