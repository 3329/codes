#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
main()
{
	int fd[2];
	int r=socketpair(AF_FILE,SOCK_DGRAM,0,fd);
	if(r==-1) printf("err:%m\n"),exit(-1);
	if(fork()){
		//shutdown(fd[1],SHUT_RD);
		//shutdown(fd[0],SHUT_WR);
		/*¶ÁÊý¾Ý*/
		char buf[256];
		while(1){
			bzero(buf,sizeof(buf));
			read(fd[1],buf,sizeof(buf)-1);
			printf("::%s\n",buf);
		}
	}
	else
	{
		//shutdown(fd[1],SHUT_RD);
		//shutdown(fd[0],SHUT_WR);
		/*Ð´*/
		while(1){
			write(fd[0],"killer",6);
			sleep(1);
		}
		
	}

	
}
