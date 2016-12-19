#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int a1=20;
static int a2=30;
const int a3=40;
int add(int a,int b){
	return  a+b;
}

main()
{
	int b1=50;
	static int b2=60;
	const int b3=70;
	
	int *p1=malloc(4);
	int *p2=malloc(4);

	printf("a1=%p\n",&a1);
	printf("a2=%p\n",&a2);
	printf("a3=%p\n",&a3);
	printf("b1=%p\n",&b1);
	printf("b2=%p\n",&b2);
	printf("b3=%p\n",&b3);
	printf("main=%p\n",main);
	printf("add=%p\n",add);
	printf("p1=%p\n",p1);
	printf("p2=%p\n",p2);
	printf("%d\n",getpid());
	while(1);
}

