#include <stdio.h>
/*#include "test.h"*/
int add(int *restrict  a,int *restrict b)
{
	(*a)++;
	return *a+*b;
}
main()
{
	int a=20;
	int b=30;
	int i;
	int sum=0;
	for(i=0;i<100;i++){
		sum+=i+a+b;
	}
	
	
	printf("%d\n",sum);
	/*printf("%d\n",TEST);*/
}


