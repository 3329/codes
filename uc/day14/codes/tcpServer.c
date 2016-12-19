#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
main()
{
	int serverfd;
	struct sockaddr_in addr;
	int r;
	char buf[256];	
	/*1.建立服务器socket*/
	serverfd=socket(PF_INET,SOCK_STREAM,0);
	if(serverfd==-1) printf("socket:%m\n"),exit(-1);
	printf("建立socket成功!\n");
	
	/*2.绑定inet通信地址*/
	addr.sin_family=PF_INET;
	addr.sin_port=htons(8888);
	inet_aton("192.168.99.85",&addr.sin_addr);
	r=bind(serverfd,(struct sockaddr*)&addr,sizeof addr);
	if(r==-1) printf("bind:%m\n"),close(serverfd),exit(-1);	
	printf("绑定地址成功!\n");
	
	/*3.监听服务器socket*/
	r=listen(serverfd,10);
	if(r==-1) printf("listen:%m\n"),close(serverfd),exit(-1);
	printf("监听成功！\n");
	
	/*4.接受客户的连接*/
	struct sockaddr_in fromaddr;
	socklen_t len=sizeof(fromaddr);
	
	while(1){
		int fd=accept(serverfd,(struct sockaddr*)&fromaddr,&len);
		if(fd==-1) {
			printf("accept:%m\n");
			break;
		}
		printf("有客户连接:%s\n",inet_ntoa(fromaddr.sin_addr));
		/*5.接受该客户的数据*/
		r=recv(fd,buf,sizeof(buf)-1,0);
		if(r==0){
			printf("客户连接关闭!\n");
		}
		if(r==-1){
			printf("网络故障!\n");
		}
		if(r>0){
			buf[r]=0;
			printf("来自客户数据:%s\n",buf);
			printf("=======================\n");
		}
		/*6.关闭连接*/	
		close(fd);	
	}	
	/*7.关闭服务器socket*/
	close(serverfd);
}
