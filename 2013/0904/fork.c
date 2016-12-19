#include "./fork.h"
#include <stdlib.h>
#include <sched.h>
const char *echo = "echo 3333333333333333333333333333333\n";
const char *pwd= "pwd\n";

void  handle(int sig)
{
	if(sig == SIGUSR1) printf("----------------------------------received SIGUSR1 signal\n");
}

int main(int argc, char** argv)
{
	int n = 0;
	char stdoutbuf[1024];
	char stderrbuf[1024];
	char buf[1024];
	int stdout_fd[2];
	int stderr_fd[2];
	int stdin_fd[2];
	pid_t pid;

	if (pipe(stdout_fd) < 0 || pipe(stderr_fd) || pipe(stdin_fd) < 0)
	{
		err_sys("pipe error");
	}

	setFdNonblocking(stdout_fd[0]);
	setFdNonblocking(stderr_fd[0]);

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid > 0)
	{
		printf("parent pid :%d\n", getpid());			
		printf("	child pid :%d\n", pid);			
		close(stdout_fd[1]);	// close write end
		close(stderr_fd[1]);	// close write end
		close(stdin_fd[0]);

		// create be Young 2013/09/11
signal(SIGUSR1, handle);
		sleep(1);

		// create epoll
		int epfd = createEvent();
		if (addEvent(epfd, stdout_fd[0], AE_READABLE) < -1 ||
				addEvent(epfd, stderr_fd[0], AE_READABLE) < -1)
		{
			printf("addEvent error\n");	
			return -1;
		}

		 //create thread manager stderr and stdout
		if (createThread(epfd) != 0)
		{
			printf("Create thread failed!\n");
		}
		
		char killstr[50] = "kill -USR1 ";
		char buff[20];
		sprintf(buff, "%d", getpid());
		printf("buff: %s\n", buff);
		strcat(killstr, buff);
		printf("killstr: %d\n", (int)strlen(killstr));

		strcat(killstr, "\n");
		printf("killstr: %d\n", (int)strlen(killstr));

		while (1)
		{
			if (fgets(buf, MAXLINE, stdin) != NULL)
			{
				write(stdin_fd[1], buf, strlen(buf));	
				usleep(1000);
				//write(stdin_fd[1], pwd, strlen(pwd));	
				write(stdin_fd[1], killstr, strlen(killstr));	
			}
		}

		//if (waitpid(pid, NULL, 0) < 0)
		//{
		//	err_sys("waitpid error");
		//}
	}
	else
	{
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


		if (execlp("/bin/tcsh", "", (char *)0) == -1)
		{
			printf("command execute error!\n");
			return -1;			
		}
	}
}

