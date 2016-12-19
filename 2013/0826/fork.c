#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/syslog.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void err_sys(char *fmt)
{
	printf("%s : %s\n",__FILE__, fmt);
}

int setFdNonblocking(int fd)
{
	int flags;

	flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1)
	{
		perror("fcntl");
		return -1;
	}

	flags |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) == -1)
	{
		perror("fcntl");
		return -1;
	}

	return 0;
}

#define AE_READABLE 1   //AE::a event
#define AE_WRITABLE 2

int createEvent()
{
	return epoll_create(1024);
}
int addEvent(int epfd, int fd, int mask)
{
	struct epoll_event ee;

	memset(&ee, 0x0, sizeof ee);

	if(mask & AE_READABLE) ee.events |= EPOLLIN | EPOLLET;;
	if(mask & AE_WRITABLE) ee.events |= EPOLLOUT;

	ee.data.fd = fd;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ee) == -1) return -1;

	return 0;
}

int waitEvent(int epfd, struct epoll_event *e)
{
	return epoll_wait(epfd, e, 64, -1);
}

int delEvent(int epfd, int fd, int mask)
{
	struct epoll_event ee;
	memset(&ee, 0x0, sizeof ee);

	if(mask & AE_READABLE) ee.events |= EPOLLIN;
	if(mask & AE_WRITABLE) ee.events |= EPOLLOUT;

	ee.data.fd = fd;
	if (epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ee) == -1) return -1;

	return 0;
}

int readPipe(int epfd, struct epoll_event *e)
{
	int ret, i, n;
	char buf[1024];
	memset(buf, 0x0, 1024);
	if((ret = waitEvent(epfd, e)) == -1)
	{
		if (errno != EINTR && errno != EAGAIN)
		{
			int err = errno;
			printf("readpipe error: %d\n", err);
			return -1;
		}
	}

	for (i=0; i<ret; i++)
	{
		int pipefd = e[i].data.fd;
		while ((n = read(pipefd, buf, 1024)) > 0)
		{
			if (n != 1024) buf[n] = '\0';
			printf("%s", buf);
		}
	}

	return ret;
}

int main(int argc, char** argv)
{
	int n = 0;
	int count = 0;
	int prev = 0;
	char stdoutbuf[1024];
	char stderrbuf[1024];
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
		close(stdout_fd[1]);	// close write end
		close(stderr_fd[1]);	// close write end
		close(stdin_fd[0]);

		sleep(1);
		
		//write(stdin_fd[1], "top\n", 4);
		//write(stdin_fd[1], "llllll\n", 7);
		//write(stdin_fd[1], "ls -la\n", 7);
		//write(stdin_fd[1], "cd ~/AOS\n", 9);
		//write(stdin_fd[1], "ls -la\n", 7);
		//write(stdin_fd[1], "pwd\n", 4);
		//write(stdin_fd[1], "ls -l lll.txt\n", 14);
		//write(stdin_fd[1], "cd llllllllll\n", 14);
		int i = 0;
		while (i < 100)
		{
			i++;	
			write(stdin_fd[1], "ls -l 2Dong\n", 12);
		}
	
// create epoll
	int epfd = createEvent();
	if (addEvent(epfd, stdout_fd[0], AE_READABLE) < -1 ||
			addEvent(epfd, stderr_fd[0], AE_READABLE) < -1)
	{
		printf("addEvent error\n");	
		return -1;
	}

	struct epoll_event *e = calloc(1024, sizeof(struct epoll_event));
	while (1)
	{
		if (readPipe(epfd, e) < 0)
		{
			printf("read pipe error\n");
		}
	}

printf("------------------%d\n", n);
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
		
			
		if (execl("/bin/tcsh", "", (char *)0) == -1)
		{
			printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
			return -1;			
		}
	}
}

