#include <stdio.h>
#include <string.h>

void printIntArray(int* a)
{
	printf("size: %d\n", sizeof(a));
	int size = sizeof(a) / sizeof(int);
	int i=0;
	for (; i<size; i++)
	{
		
		printf("%d: %d\n", i, *(a++));
	}
}
int main()
{
	char * s = "abcdefghjkk";
	printf("%s\n", s);

	int a[] = {10, 20, 30, 40, 50};
	int i = 0;
	for (; i<5; i++)
	{
		printf("%d", a[i]);
	}

	printf("========================\n");
	printIntArray(a);
}

