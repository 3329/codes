#include <stdio.h>
int main()
{
	int a=InputInt("输入被加数");
	int b=InputInt("输入加数");
	int c=add(a,b);
	printf("%d+%d=%d\n",a,b,c);
	return 0;
}
