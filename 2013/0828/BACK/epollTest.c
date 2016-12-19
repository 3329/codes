#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h> // htons
#include <string.h> // bzero
#include <fcntl.h>

int main(int argc, char* argv[])
{
	pid_t child;
	int pipefd[2];
	int e_fd = epoll_create(10);
	if (-1 == e_fd)
	{
		perror("epoll_create");
		exit(1);
	}    

	pipe(pipefd);
	printf("fd0: %d, fd1: %d \n",pipefd[0], pipefd[1]);

	if ((child = fork()) == -1)
	{
		perror("fork");
		close(e_fd);
		exit(1);
	}

	if (child == 0)
	{
		close(pipefd[0]);
		sleep(1);
		write(pipefd[1],"a", 1);    
		sleep(2);
		write(pipefd[1],"b",1);
		sleep(3);
		close(pipefd[1]);
		// socket
		{
			int fd, status;
			struct sockaddr_in remote;
			remote.sin_family = AF_INET;
			remote.sin_port = htons(5930);
			remote.sin_addr.s_addr = inet_addr("192.168.1.213");

			fd = socket(AF_INET, SOCK_STREAM, 0);

			sleep(3);
			status = connect(fd, (struct sockaddr*)&remote, sizeof(struct sockaddr));
			if (status == -1)
			{
				perror("connect");
				close(fd);
				exit(1);
			}

			sleep(2);
			if (send(fd, "hello", 5, 0) == -1)
			{
				perror("send");
			}
			close(fd);
		}    

	}
	else
	{
		struct epoll_event evs[10];
		struct epoll_event ev;
		struct P_ATR{
			int fd;
		} pipe_atr;

		int nds = 0, i;
		close(pipefd[1]);
		pipe_atr.fd = pipefd[0];

		ev.data.fd = pipefd[0];
		//ev.data.ptr = &pipe_atr; // 不传入data.ptr
		ev.events = EPOLLIN;
		epoll_ctl(e_fd, EPOLL_CTL_ADD, pipefd[0], &ev);

		//sleep(5);
		nds = epoll_wait(e_fd, evs, 10, -1);

		printf("epoll_wait ret %d\n", nds);

		for (i = 0; i < nds; i++)
		{
			int fd;
			printf("evs[%d].data.fd: %d, ", i, fd = evs[i].data.fd); // 我们在上面没有传入data.ptr，此时系统会返回data.fd
			// printf("event fd: %d\n", fd = ((struct P_ATR*)(evs[i].data.ptr))->fd);
			if ( fd == pipefd[0])
			{
				char readbuf[80];
				int readbytes = read(pipefd[0], readbuf, 1);
				readbuf[readbytes] = 0;
				printf ("pipe event catch, recvdata = %s, size = %d\n", readbuf, readbytes);
			}
		}

		ev.events = EPOLLIN;
		epoll_ctl(e_fd, EPOLL_CTL_MOD, pipefd[0], &ev);
		nds = epoll_wait(e_fd, evs, 10, -1);

		printf("epoll_wait ret %d\n", nds);

		for (i = 0; i < nds; i++)
		{
			int fd;
			printf("evs[%d].data.fd: %d, ", i, fd = evs[i].data.fd);
			// printf("event fd: %d\n", fd = ((struct P_ATR*)(evs[i].data.ptr))->fd);
			if ( fd == pipefd[0])
			{
				char readbuf[80];
				int readbytes = read(pipefd[0], readbuf, 1);
				readbuf[readbytes] = 0;
				printf ("pipe event catch, recvdata = %s, size = %d\n", readbuf, readbytes);
			}
		}

		epoll_ctl(e_fd, EPOLL_CTL_MOD, pipefd[0], &ev);
		nds = epoll_wait(e_fd, evs, 10, -1);

		printf("epoll_wait ret %d\n", nds);

		for (i = 0; i < nds; i++)
		{
			int fd;
			printf("evs[%d].data.fd: %d, ", i, fd = evs[i].data.fd);
			// printf("event fd: %d\n", fd = ((struct P_ATR*)(evs[i].data.ptr))->fd);
			if ( fd == pipefd[0])
			{
				char readbuf[80];
				int readbytes = read(pipefd[0], readbuf, 1);
				readbuf[readbytes] = 0;
				printf ("pipe event catch, recvdata = %s, size = %d\n", readbuf, readbytes);
			}
		}
		close(pipefd[0]);

		// socket
		{
			struct sockaddr_in addr;
			struct sockaddr_in remote;
			int newfd;

			int sockfd = socket(AF_INET, SOCK_STREAM, 0);
			if (-1 == sockfd)
			{
				perror("socket");
				exit(0);
			}        

			printf("new socket fd: %d\n", sockfd);
			addr.sin_family = AF_INET;
			addr.sin_port = htons(5930);
			addr.sin_addr.s_addr = INADDR_ANY;

			bzero(&addr.sin_zero, 8);

			if (bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) == -1)    
			{
				perror("bind");
				close(sockfd);
				exit(1);
			}        

			pipe_atr.fd = sockfd;
			ev.data.fd = sockfd;
			ev.data.ptr = &pipe_atr; // 传入data.ptr
			ev.events = EPOLLIN;
			epoll_ctl(e_fd, EPOLL_CTL_ADD, sockfd, &ev);

			if (listen(sockfd, 5) == -1)
			{
				perror("listen");
				exit(1);
			}

			nds = epoll_wait(e_fd, evs, 10, -1);
			printf("epoll_wait ret %d\n", nds);

			for (i = 0; i < nds; i++)
			{
				int fd;
				socklen_t len;
				int inds;
				printf("evs[%d].data.fd: %d, ", i, evs[i].data.fd); // 系统不会回填data.fd，其值是随机数字
				printf("event fd: %d\n", fd = ((struct P_ATR*)(evs[i].data.ptr))->fd); // 系统返回用户传入的data.ptr
				if ( fd == sockfd)
				{
					len = sizeof (struct sockaddr);
					newfd = accept(sockfd, (struct sockaddr*)&remote, &len);
					if (-1 == newfd)
					{
						perror("accept");
						close(sockfd);
						exit(1);
					}

					printf("new link create success, fd: %d\n", newfd);

					struct P_ATR new_atr;
					new_atr.fd = newfd;
					ev.data.fd = newfd;
					ev.data.ptr = &new_atr;
					ev.events = EPOLLIN;
					epoll_ctl(e_fd, EPOLL_CTL_ADD, newfd, &ev);

					inds = epoll_wait(e_fd, evs, 10, -1);
					printf("epoll_wait ret %d\n", inds);

					for (i = 0; i < inds; i++)
					{    
						int fd;
						printf("evs[%d].data.fd: %d, ", i, evs[i].data.fd);
						printf("event fd: %d\n", fd = ((struct P_ATR*)(evs[i].data.ptr))->fd);
						if ( fd == newfd)
						{
							char readbuf[80];
							int readbytes = read(fd, readbuf, sizeof(readbuf));
							readbuf[readbytes] = 0;
							printf ("pipe event catch, dataptr = %p, recvdata = %s, size = %d\n", evs[i].data.ptr, readbuf, readbytes);
						}
					}
					close(newfd);
					close(sockfd);                    
				}
			}            
		}    
	}

	close(e_fd);
	return 0;

}
