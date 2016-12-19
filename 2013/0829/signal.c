#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sig_cld(int signo)
{
	pid_t pid;
	int status;
	printf("SIGCHLD receive\n");
	if (signal(SIGCHLD, sig_cld) == SIG_ERR)
		perror("signal error");
	if ((pid = wait(&status)) < 0)
		perror("wait error");
	printf("pid = %d\n", pid);
}

int main()
{
	pid_t pid;
	if (signal(SIGCHLD, sig_cld) == SIG_ERR)
		perror("signal error!");
	if ((pid = fork()) < 0)
	{
		perror("fock error");
	}
	else if (pid == 0)
	{
		sleep(2);
		_exit(0);			
	}
	pause();// parent
		
	return 0;
}

