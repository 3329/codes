#include <unistd.h>
#include <stdio.h>
main()
{
	printf("���̴���ǰ!\n");
	pid_t pid=57575;
	pid=fork();
	if(pid==0){		
		while(1)
		{
			printf("�ӽ���--1\n");
		}
	}
	if(pid)
	{		
		while(1)
		{
			printf("������------2\n");
		}
	}
	
}
