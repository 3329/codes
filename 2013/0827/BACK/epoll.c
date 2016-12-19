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

typedef struct config
{
	char *logfile;
	int syslog_enabled;
}LogConfig;

typedef enum{
	logDebug,
	logInfo,
	logWarning,
	logFetal
}LogLevel;


void myLog(LogLevel level, LogConfig *logConf, const char *fmt, ...)
{
	const int syslogLevelMap[] = { LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERR };

	const char *sInfo[] = {"DEBUG", "INFO", "WARNING", "FETAL" };

	time_t now = time(NULL);
	va_list ap;
	FILE *fp;
	char buf[64];
	char msg[4096];

	if (level < 0)
		return;

	va_start(ap, fmt);
	vsnprintf(msg, sizeof(msg), fmt, ap);
	va_end(ap);

	if (NULL != logConf)
	{
		fp = (logConf->logfile == NULL) ? stdout : fopen(logConf->logfile, "a");
		if (!fp)
			return;

		if (logConf->syslog_enabled)
			syslog(syslogLevelMap[level], "%s", msg);

	}
	else
	{
		fp = stdout;
	}

	strftime(buf, sizeof(buf), "%d %b %H:%M:%S", localtime(&now));

	fprintf(fp, "[%d] %s [%s]: %s\n", (int) getpid(), buf, sInfo[level], msg);
	fflush(fp);

	if (logConf && logConf->logfile)
		fclose(fp);
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
#include <sys/syslog.h>
int myRead(int epfd, int pipefd0, struct epoll_event *e)
{
	int ret, i;
	if((ret = waitEvent(epfd, e)) < 0){
		myLog(logFetal, NULL, "epoll_wait error: %s", strerror(errno));
		return -1;
	}

	if(ret > 0){
		LogConfig conf;
		conf.logfile = "test.log";
		conf.syslog_enabled = 1;

		for(i = 0; i< ret; i++){
			char rBuf[1024];
			memset(rBuf, 0x0, 1024);
			read(pipefd0, rBuf, 1024);

			myLog(logInfo, NULL, "child -> %s\n", rBuf);
		}
	}

	return ret;
}

#if 01

int main()
{
	int pipefd[2];
	int count = 15;
	if(pipe(pipefd) < 0) return -1;

	pid_t pid = fork();
	if(pid < 0) return -1;

	int pipeReadfd = pipefd[0];
	int pipeWritefd = pipefd[1];

	setFdNonblocking(pipeReadfd);

	if(0 == pid){
		int i = 0;
		int epfd = createEvent();

		if(addEvent(epfd, pipeReadfd, AE_READABLE) < -1) return -1;

		struct epoll_event *e = calloc(1024, sizeof(struct epoll_event));

		while(i++ < count){
			int ret = 0;
			if((ret = myRead(epfd, pipeReadfd, e)) < 0){
				//Here we do not check the situation that the "ret" less than 0
				//stracing or gdbing this process will trigger a siglarm which will cause "ret == -1"
			}
			//                              printf("ret val: %d\n", ret);
		}

		close(epfd);
		free(e);
		printf("child finished...\n");

	}else{
		int i = 0;

		while(i++ < count){
			usleep(100000);
			//                      char buf[1204];
			//                      memset(buf, 0x0, 1024);
			//                      fgets(buf, 10, stdin);
			write(pipeWritefd, "hello", 1024);
		}

		printf("parent finished...\n");
	}

	close(pipefd[0]);
	close(pipefd[1]);
	usleep(10000);
	return 0;
}
#endif


