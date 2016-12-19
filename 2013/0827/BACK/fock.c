#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <fcntl.h>

void err_sys(char *fmt)
{
	printf("%s : %s\n",__FILE__, fmt);
}

int main(int argc, char** argv)
{
	// loop to get the cmd 
	
	int n = 0;
	int count = 0;
	int prev = 0;
	char stdoutbuf[1024];
	char stderrbuf[1024];
	char *cmd;
	char line[80];
	int stdout_fd[2];
	int stderr_fd[2];
	int stdin_fd[2];
	int flags;
	pid_t pid;

	if (pipe(stdout_fd) < 0 || pipe(stderr_fd) || pipe(stdin_fd) < 0)
	{
		err_sys("pipe error");
	}
	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid > 0)
	{
		close(stdout_fd[1]);	// close write end
		close(stderr_fd[1]);	// close write end
		close(stdin_fd[0]);

		sleep(1);
		
		write(stdin_fd[1], "llllll\n", 7);
		write(stdin_fd[1], "ls -la\n", 7);
		write(stdin_fd[1], "pwd\n", 4);
		write(stdin_fd[1], "ls -l lll.txt\n", 14);


	//	flags = fcntl(STDOUT_FILENO, F_GETFL);
	//	flags |= O_NONBLOCK;
	//	if (fcntl(STDOUT_FILENO, F_SETFL, flags) == -1) {
	//		perror("fcntl");
	//	}
	//	printf("parent pid: %d\n", getpid());
		// read infomation from pipe
		while ((n = read(stdout_fd[0],stdoutbuf, 1024)) > 0) 
		{
			count += n;
			prev = n;
			if (n != 1024)
			{
				stdoutbuf[n] = '\0';
				printf("%s", stdoutbuf);
				printf("------------------%d\n", n);
				break;
			}
			printf("%s", stdoutbuf);
			printf("------------------%d\n", n);
		}

		n = 0;
		count = 0;
		while ((n = read(stderr_fd[0],stderrbuf, 1024)) > 0) 
		{
			count += n;
			if (n != 1024) stdoutbuf[n] = '\0';
printf("%s", stderrbuf);
		}

printf("------------------%d", n);
		//close(stdout_fd[0]);
		//close(stderr_fd[0]);
		//if (waitpid(pid, NULL, 0) < 0)
		//{
		//	err_sys("waitpid error");
		//}
	}
	else {
		close(stdout_fd[0]);	// close read end
		close(stderr_fd[0]);	// close read end
		if (stdin_fd[0] != STDIN_FILENO)
		{
			if (dup2(stdin_fd[0], STDIN_FILENO) != STDIN_FILENO)
			{
				err_sys("dup2 error");
			}

			close(stdin_fd[0]);	// don't need this after dup2
		}	
		if (stdout_fd[1] != STDOUT_FILENO)
		{
			if (dup2(stdout_fd[1], STDOUT_FILENO) != STDOUT_FILENO)
			{
				err_sys("dup2 error");
			}

			close(stdout_fd[1]);	// don't need this after dup2
		}

		if (stderr_fd[1] != STDERR_FILENO)
		{
			if (dup2(stderr_fd[1], STDERR_FILENO) != STDERR_FILENO)
			{
				err_sys("dup2 error");
			}

			close(stderr_fd[1]);	// don't need this after dup2
		}
		
			
		if (execl("/bin/bash", "", (char *)0) == -1)
		{
			printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
			return -1;			
		}
	}
}

