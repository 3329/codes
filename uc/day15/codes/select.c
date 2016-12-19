#include <stdio.h>
#include <sys/select.h>
main()
{
	fd_set fds;
	char buf[256];
	int r;
	
	
	while(1){
		FD_ZERO(&fds);
		FD_SET(0,&fds);
		select(1,&fds,0,0,0);
		r=read(0,buf,255);
		if(r==0) break;
		buf[r]=0;
		printf("::%s\n",buf);
	}
	
}
