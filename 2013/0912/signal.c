#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// shell format:
// kill -USR1 pid
// kill -USR2 pid
static void sig_usr(int signum)
{
	if (signum == SIGUSR1)	printf("received SIGUSR1 111111\n");
	else if (signum == SIGUSR2)  printf("received SIGUSR2 222222\n");
	else printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
}

main()
{
	printf("pid: %d\n", getpid());
	if (signal(SIGUSR1, sig_usr))
		printf("can't catch SIGUS1 signal\n");
			
	if (signal(SIGUSR2, sig_usr))
		printf("can't catch SIGUS2 signal\n");
	while (1)
	{
		pause();
	}
}

