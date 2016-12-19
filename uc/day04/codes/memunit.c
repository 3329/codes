#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

main()
{
	int *p=malloc(4);
	printf("%p\n",p);
	*p=20;
	*(p+132*1024)=20;
	printf("%d\n",getpid());
	while(1);
	/*
	printf("%p\n",p);
	free(p);
	*p=20;
	int *p1=malloc(4);
	printf("%p\n",p1);
	printf("%d\n",*p1);
	*/
}
