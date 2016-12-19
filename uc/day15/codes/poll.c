#include <stdio.h>
#include <poll.h>

main()
{
	struct pollfd fds;
	char buf[256];
	int r;
	fds.fd=0;
	fds.events=POLLIN;
	fds.revents=0;
	
	while(1){
		poll(&fds,1,-1);
		if(fds.revents & POLLIN){
			printf("гаЪ§Он!\n");	
			r=read(fds.fd,buf,255);
			if(r==0) break;
			buf[r]=0;
			printf("::%s",buf);
		}
	}
}