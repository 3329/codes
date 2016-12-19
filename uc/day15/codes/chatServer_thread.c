#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
int sfd;
int fds[4096];
pthread_t ths[4096];
int id=0;
struct sockaddr_in addr={0};

void *clienth(void *d){
	int idx=*((int*)d);/*记录描述符号位置*/
	char buf[256];
	int r,i;
	while(1){
		/*2.1.循环接受客户数据*/
		r=recv(fds[idx],buf,sizeof(buf)-1,0);
		if(r<=0) {
			printf("有客户退出!\n");
			close(fds[idx]);
			fds[idx]=-1;
			break;
		}	
		buf[r]=0;
		printf("聊天信息:%s",buf);
		/*2.2.广播客户数据*/
		for(i=0;i<=id;i++){
			if(fds[i]!=-1){
				send(fds[i],buf,strlen(buf),0);
			}
		}
	}
}

main()
{	
	int i;
	int r;
	for(i=0;i<4096;i++){
		fds[i]=-1;
	}
	addr.sin_family=AF_INET;
	addr.sin_port=htons(10000);
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	/*1.1.建立服务器socket*/
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1) exit(-1);
	printf("建立socket成功1\n");
	/*1.2.绑定通信地址*/
	r=bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) exit(-1);
	printf("绑定成功!\n"); 
	/*1.3.监听*/
	r=listen(sfd,10);
	if(r==-1) exit(-1);
	printf("监听成功!\n");
	while(1){
		/*1.4.循环接受客户连接*/
		fds[id]=accept(sfd,0,0);
		if(fds[id]==-1) break;
		/*1.5.创建子线程*/
		printf("有客户连接!\n");	
		int tmpid=id;	
		pthread_create(&ths[id],0,clienth,&tmpid);		
		id++;
	}
	/*关闭所有连接*/
	/*终止所有线程*/
	close(sfd);
	printf("系统崩溃！\n");
}




