#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
struct ICMP_header {
	unsigned char type; /* Error type */
	unsigned char code; /* Error code */
	unsigned short checksum; /* Message checksum */
	unsigned short msg[1024]; /* Additional data description */
} ;

main()
{
	//读取的原生数据包
	struct ICMP_header buf;
	int fd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
	if(fd==-1)
	{	
		printf("socket error:%m\n");exit(-1);
	}
	while(1)
	{
		//读取数据
		bzero(&buf,sizeof(buf));
		int r=recv(fd,&buf,sizeof buf,0);
		if(r<=0)
		{
			printf("没有读取到数据\n");
			break;
		}
		else
		{
			printf("大小:%d\n",r);
			printf("type:%d,code:%d\n",buf.type,buf.code);
		}
	}	
	close(fd);
}
/*
建立在IP之上的协议有ICMP，TCP，UDP，IGMP协议等

*/


