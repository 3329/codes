#include <stdio.h>
#include <unistd.h>
#include <signal.h>

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
	signal(SIGCHLD, phandle);
	if (execlp("/bin/ls", "ls", (char *)0) == -1)
	{
		printf("command execute error!\n");
		return -1;			
	}
}

