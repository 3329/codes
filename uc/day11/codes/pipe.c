#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
main()
{
	int fd[2];
	pipe(fd);	
	if(fork()){
		char buf[10];
		//close(fd[1]);
		while(1){
			bzero(buf,10);
			read(fd[0],buf,10);
			printf(":%s\n",buf);
		}
	}
	else{
		//close(fd[0]);
		while(1){
			write(fd[1],"Hello",5);
			sleep(1);
		}
	}
	close(fd[0]);
	close(fd[1]);
}

