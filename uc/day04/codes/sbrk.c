#include <unistd.h>
#include <stdio.h>
main()
{
	int *p1=sbrk(4);
	int *p2=sbrk(1);
	int *p3=sbrk(1);
	int *p4=sbrk(4);
	int *p5=sbrk(0);
	printf("%p\n",p1);
	printf("%p\n",p2);
	printf("%p\n",p3);
	printf("%p\n",p4);
	printf("%p\n",p5);
	sbrk(-4);
	sbrk(-1);
	printf("%p\n",sbrk(0));
	brk(p1);
	*p1=20;
	//*p=20;	
	//printf("%p\n",p);
	//printf("%d\n",getpid());
	//while(1);
}

