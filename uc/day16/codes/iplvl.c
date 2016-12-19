#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

main()
{
	int fd;
	char buf[4096];
	int r;
	struct ip *hdr;
	fd=socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
	if(fd==-1) printf("socket:%m\n"),exit(-1);
	
	while(1){
		r=recv(fd,buf,sizeof(buf),0);
		if(r>0){
			printf("数据包长度:%d\n",r);
			hdr=(struct ip*)buf;
			printf("类型:%d\n",hdr->ip_p);
			printf("类型:%s->%s\n",
						 inet_ntoa(hdr->ip_src),
						 inet_ntoa(hdr->ip_dst));
		}		
	}
}
