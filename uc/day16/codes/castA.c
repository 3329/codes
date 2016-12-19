#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/*广播端*/
main()
{
	int fd;
	int val=1;
	int r;	
	/*建立socket*/
	fd=socket(AF_INET,SOCK_DGRAM,0);
	if(fd==-1) exit(-1);
	printf("socket建立成功!\n");
	/*设置socket选项为SO_BROADCAST*/
	r=setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&val,sizeof(val));
	if(r==-1) exit(-1);
	printf("设置广播成功!\n");
	/*广播数据*/
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9999);
	addr.sin_addr.s_addr=inet_addr("192.168.180.255");
	while(1){
		sendto(fd,"this is a dog!",14,0,
					 (struct sockaddr*)&addr,sizeof(addr));
		sleep(1);
	}
	
}

