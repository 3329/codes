#include <stdio.h>

#define swap(t, x, y) { t _z;	\
						_z = y;	\
						y = x;	\
						x = _z;	}

int main()
{
	int a1 = 10;
	int a2 = 20;
	printf("Before swap: %d & %d.\n", a1, a2);
	swap(int, a1, a2);
	printf("After swap: %d & %d.\n", a1, a2);
}

