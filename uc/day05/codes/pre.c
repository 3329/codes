#include <stdio.h>
#pragma GCC poison add  substract

#pragma GCC dependency "gcc.c"

/*#define NUM 9999*/
int main()
{
#line 1000
#warning "this is a information"
/*#error "this is a big problem!"*/
	printf("Hello World!\n");
	/*printf("Hello World:%d\n",NUM);*/
#ifdef NUM
	printf("%d\n",NUM);
#else
	printf("û�ж���NUM��\n");
#endif	 
	return 0;
}

