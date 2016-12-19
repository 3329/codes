#include <iostream>
#include <mcheck.h>
#include <stdlib.h>
using namespace std;
int main()
{
	setenv("MALLOC_TRACE","output",1);
	mtrace();
	int *p1 = new int;
	int *p2 = new int;
	int *p3 = (int*)malloc(sizeof(int));
	int *p4 = (int*)malloc(sizeof(int));

	delete p1;
	free(p3);

	return 0;
}
