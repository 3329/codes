#include <stdio.h>
#include <stdlib.h>
main()
{
	int *p=malloc(4);
	*p=9999;
	printf("%p\n",p);

	while(1);
}

