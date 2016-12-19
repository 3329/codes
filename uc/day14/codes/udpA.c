#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
int socketfd;
struct sockaddr_in addr;
int r;
char buf[256];

void handle(int s){
	/*5.关闭socket*/
	close(socketfd);
	exit(0);
}
main()
{
	/*0.处理ctrl+c的信号*/
	signal(SIGINT,handle);
	/*1.建立socket*/
	socketfd=socket(PF_INET,SOCK_DGRAM,0);
	if(socketfd==-1) printf("socket:%m\n"),exit(-1);
	printf("建立socket成功!\n");
	
	/*2.构建inet通信地址*/
	addr.sin_family=PF_INET;
	addr.sin_port=htons(11111);
	inet_aton("192.168.180.67",&addr.sin_addr);
	/*addr.sin_addr.s_addr=inet_addr("192.168.180.67");*/
	/*3.绑定通信地址*/
	r=bind(socketfd,(struct sockaddr*)&addr,sizeof addr);
	if(r==-1) printf("bind:%m\n"),close(socketfd),exit(-2);
	printf("绑定地址成功!\n");	
	/*4.接受数据recv/recvfrom*/
	struct sockaddr_in fromaddr;
	socklen_t len=sizeof(fromaddr);	
	while(1){
		r=recvfrom(socketfd,buf,sizeof(buf)-1,0,
							 (struct sockaddr*)&fromaddr,&len);
		if(r==-1) break;
		buf[r]=0;/*添加终止符号*/
		printf("来自:%s的数据:%s\n",
					 inet_ntoa(fromaddr.sin_addr),buf);
		/*反发数据回去*/
		sendto(socketfd,"OK!",3,0,
					 (struct sockaddr*)&fromaddr,len);
	}
	close(socketfd);
}
