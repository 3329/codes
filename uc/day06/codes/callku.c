#include <stdio.h>
#include <unistd.h>
int main()
{
	int a=InputInt("����Ҫ�ж�������:");
	if(IsPrimer(a)){
		printf("%d������!\n",a);
	}
	else{
		printf("%d�Ǻ���!\n",a);
	}
	printf("%d\n",getpid());
	while(1);
	return 0;
}
