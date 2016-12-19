#include <unistd.h>
#include <signal.h>
#include <stdio.h>
void handle(int s)
{
	printf("信号SIGINT＝2被程序处理!\n");
}
main()
{
	int i=0;
	int sum=0;
	signal(SIGWINCH,handle);
	printf("%d\n",getpid());
	for(i=0;i<100;i++){
		sum+=i;
		sleep(1);
	}
	printf("sum=%d\n",sum);
}
