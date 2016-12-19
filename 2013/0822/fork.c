#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	if ((pid = fork()) < 0)
	{
		perror("fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
		int i = 3;
		for (; i>0; i--)
		{
			printf("This is the child\n");
			sleep(1);
		}

		exit(3);
	}
	else
	{
		int stat_val;
		waitpid(pid, &stat_val, 0);
		if (WIFEXITED(stat_val))
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
		else if (WIFSIGNALED(stat_val))
			printf("Child terminated abnormally, signal %d\n", WTERMSIG(stat_val));
	}

	return 0;
}


