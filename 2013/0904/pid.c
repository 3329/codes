#include <stdio.h>
#include <unistd.h>
#include <signal.h>

pid_t curppid;
void  handle(int sig,siginfo_t *info,void *d){
	union sigval val;
	val.sival_int = 9;
	if(sig==SIGCHLD){
		printf("sigchld signalPPPPPPPP\n");
		sigqueue(curppid,35,val);/*发送信号给子进程*/
	}
}

void phandle(int signum)
{
	if (signum == 35)
	{
		printf("++++++++++++++++++++Alksdklaks\n");
	}
}
main()
{
	pid_t pid;
	curppid = getpid();
	if ((pid = fork()) < 0)
	{
		perror("fork");
	}
	else if (pid == 0)
	{
		printf("child pid : %d\n", getpid());
		struct sigaction act = {0};
		act.sa_sigaction = handle;
		sigemptyset(&act.sa_mask);
		sigfillset(&act.sa_mask);
		act.sa_flags = SA_SIGINFO;
		sigaction(SIGCHLD, &act, NULL); 

		if (execlp("/bin/bash", "ls", (char *)0) == -1)
		{
			printf("command execute error!\n");
			return -1;			
		}
		printf("command execute error!\n");
	}
	else
	{
		signal(35, phandle);
		sleep(3);
		printf("------------------\n");

	}
}

