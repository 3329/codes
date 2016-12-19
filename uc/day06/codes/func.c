#include <stdio.h>
__attribute((constructor)) int Add(int a,int b) 
{
	return a+b;
}

int main()
{
	/*int(*p)(int,int);=add*/
	typedef int(*P)(int);
	P p;
	p=(P)Add;
	
	int r=p(20);
	
	printf("%d\n",r);
	return 0;
}
