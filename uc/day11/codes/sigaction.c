#include <signal.h>
#include <unistd.h>
#include <stdio.h>
void handle(int s){
	printf("信号处理!\n");
}
void handle2(int s,siginfo_t *info,void *d)
{
	printf("%d:发送信号:%d!\n",info->si_pid,info->si_int);
}

main()
{
	struct sigaction act={0};
	act.sa_handler=handle;
	act.sa_sigaction=handle2;
	
	sigemptyset(&act.sa_mask);
	sigfillset(&act.sa_mask);
	
	act.sa_flags=SA_SIGINFO;
	
	sigaction(SIGINT,&act,NULL);
	while(1);
}
