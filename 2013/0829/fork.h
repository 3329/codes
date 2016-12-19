#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/syslog.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#define MAXLINE 100

#define AE_READABLE 1   //AE::a event
#define AE_WRITABLE 2

static char buf[1000000];
const char *echostr = "3333333333333333333333333333333\n";
int crt_idx = 0;
const int flag_length = 32; 

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
	return epoll_wait(epfd, e, 64, 100);
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
	const int max_size = 1000000;
	const int max_echo_waits = 50;
	int not_canceled = 1;
	char buf[100];

	int ret, i, n;
	//memset(buf, 0x0, 100000);
	int num_echo_waits = 0;
	if((ret = waitEvent(epfd, e)) == -1)
	{
		if (errno != EINTR && errno != EAGAIN)
		{
			int err = errno;
			printf("readpipe error: %d\n", err);
			return -1;
		}
	}

	if (ret == 0)
	{
		// It is timeout. This means it has read in all the response contents (possibly). 
		// It checks whether the ending contents are "3333333333333333". If not, it means
		// there are still contents. It needs to go back to read again. 
		//if (crt_idx >= flag_length && strncmp(&buf[crt_idx-flag_length], echostr, flag_length) == 0)
		//{
		//	// It has read in all the responses. 
		//	buf[crt_idx-flag_length] = '\0';
		//	//return buf;
		//	return 0;
		//}
		//continue;
	}

	for (i=0; i<ret; i++)
	{
		int pipefd = e[i].data.fd;
		int prev = 0;
		while ((n = read(pipefd, buf, 100)) > 0)
		{
			//if (n != 100) buf[crt_idx] = '\0';
			//else if (n == 100) buf[n] = '\0';
			//printf("%s", buf);
			
			buf[n] = '\0';
			printf("%s", buf);
		}
	}

	return ret;
}

void *threadFunc(void* epfd)
{
	struct epoll_event *e = calloc(1024, sizeof(struct epoll_event));
	while(1)
	{
		if (readPipe((int)epfd, e) < 0)
		{
			printf("read pipe error\n");
		}
		// check the reslut whether has "333333333"
		// if it does not have, read again
		// if have return the value
		/*
		if (crt_idx >= flag_length && strncmp(&buf[crt_idx-flag_length], echostr, flag_length) == 0)
		{
			// It has read in all the responses. 
			buf[crt_idx-flag_length] = '\0';
			printf("%s", buf);
			crt_idx = 0;
			buf[0] = '\0';
		}
		*/

	}
	// free
}

int createThread(int epfd)
{
	pthread_t ntid;
	int err = pthread_create(&ntid, NULL, threadFunc, (void*)epfd);
	if (err != 0)
	{
		printf("can't create thread: %s\n", strerror(err));
		return 1;
	}
	return 0;
}
