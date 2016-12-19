#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
int sockfd;
struct sockaddr_in addr;
int r;
char buf[256];/*接受键盘输入数据，与发送数据*/
char data[256];/*接受来自A端的数据*/

void handle(int s){
	close(sockfd);
	exit(0);	
}

main()
{
	/*0.处理ctrl+c信号*/
	signal(SIGINT,handle);
	/*1.建立socket*/
	sockfd=socket(PF_INET,SOCK_DGRAM,0);
	if(sockfd==-1) printf("socket:%m\n"),exit(-1);
	printf("建立socket成功!\n");
	
	/*2.构建inet通信地址*/
	addr.sin_family=PF_INET;
	addr.sin_port=htons(11111);
	inet_aton("192.168.180.67",&addr.sin_addr);
	
	while(1){
		/*3.输入数据*/
		r=read(0,buf,sizeof(buf)-1);
		if(r<=0) break;
		buf[r]=0;
		/*4.发送数据*/
		sendto(sockfd,buf,strlen(buf),0,
					 (struct sockaddr*)&addr,sizeof(addr));
		/*5.接受A发来的数据*/
		r=recv(sockfd,data,sizeof(data)-1,0);
		if(r<=0) break;
		data[r]=0;
		/*6.打印接受的数据*/
		printf("来自A端的数据:%s\n",data);
	}
	/*7.关闭socket*/	
	close(sockfd);
}
