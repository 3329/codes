#include <stdio.h>

int InputInt(const char *info)
{
	int r;
	printf("%s\n",info);
	scanf("%d",&r);
	return r;
}
