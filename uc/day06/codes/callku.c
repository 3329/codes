#include <stdio.h>
#include <unistd.h>
int main()
{
	int a=InputInt("输入要判定的整数:");
	if(IsPrimer(a)){
		printf("%d是素数!\n",a);
	}
	else{
		printf("%d是和数!\n",a);
	}
	printf("%d\n",getpid());
	while(1);
	return 0;
}
