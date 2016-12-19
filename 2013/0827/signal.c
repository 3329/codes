#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sig_usr(int signo)
{
	if (signo == SIGUSR1)
	{
		printf("received SIGUSER1\n");
	}
	else if (signo == SIGUSR2)
	{
		printf("received SIGUSER2\n");
	}
	else
	{
		printf("received signal %d\n", signo);
	}
}

int main()
{
printf("pid : %d\n", getpid());
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
	{
		printf("can't catch SIGUSR1\n");	
	}
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
	{
		printf("can't catch SIGUSR2\n");	
	}
	while (1)
	{
		pause();
	}
	return 0;
}

