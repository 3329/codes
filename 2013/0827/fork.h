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
#include <pthread.h>
#define MAXLINE 100

#define AE_READABLE 1   //AE::a event
#define AE_WRITABLE 2
char display[100000];


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
	char buf[100];
	//memset(buf, 0x0, 100000);
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
		memset(buf, 0x0, sizeof(buf));
		int pipefd = e[i].data.fd;
		while ((n = read(pipefd, buf, 100)) > 0)
		{
		
			if (n != 100) buf[n] = '\0';
			else if (n == 100) buf[n] = '\0';
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
	}
	// free
}

int createThread(int epfd)
{
	pthread_t ntid;
	//int err = pthread_create(&ntid, NULL, threadFunc(epfd, e), NULL);
	int err = pthread_create(&ntid, NULL, threadFunc, (void*)epfd);
	if (err != 0)
	{
		printf("can't create thread: %s\n", strerror(err));
		return 1;
	}
	return 0;
}
