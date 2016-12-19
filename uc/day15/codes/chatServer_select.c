#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
main()
{
	int sfd;/*服务器socket*/
	int fds[4096];/*存储所有的连接客户socket:-1表示断线*/
	int id;/*已经连接的最大数*/
	fd_set allfds;/*被监视的描述符号，同时返回已经改变的描述符号*/
	int maxfd;/*最大描述符号*/
	char buf[256];/*临时存放每个客户的数据*/
	int r;/*临时存放函数返回值*/
	struct sockaddr_in addr;/*服务器通信地址*/
	int i,j;
	/*0.初始化数据*/
	sfd=-1;
	for(i=0;i<4096;i++){
		fds[i]=-1;
	}
	id=0;
	FD_ZERO(&allfds);
	maxfd=-1;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(10000);
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	/*1.创建服务器 socket,帮定地址，监听*/
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1) exit(-1);
	printf("服务器socket建立成功!\n"); 
	
	r=bind(sfd,(struct sockaddr*)&addr,sizeof addr);
	if(r==-1) exit(-1);
	printf("绑定成功!\n");
	
	r=listen(sfd,10);
	if(r==-1) exit(-1);
	printf("监听成功!\n");
	
	while(1){
		/*2.初始化要监控描述符号(包括服务器socket与客户socket)*/
		FD_ZERO(&allfds);
		maxfd=-1;
		/*2.1.把服务器socket加入监视集合*/
		FD_SET(sfd,&allfds);
		maxfd=maxfd>=sfd?maxfd:sfd;
		/*2.2.把客户socket加入监视集合*/
		for(i=0;i<id;i++){
			if(fds[i]!=-1){
				FD_SET(fds[i],&allfds);
				maxfd=maxfd>=fds[i]?maxfd:fds[i];
			}
		}
		/*2.3.开始监控*/
		r=select(maxfd+1,&allfds,0,0,0);
		if(r==-1) {
			printf("系统崩溃!\n");
			/*关闭所有客户*/
			for(i=0;i<id;i++){
				if(fds[i]!=-1){
					close(fds[i]);
					fds[i]=-1;
				}
			}
			/*关闭服务器socket*/
			close(sfd);
			/*退出*/
			exit(-1);
		}
		/*3.处理改变的描述符号*/
		/*3.1.处理服务器socket:接受新客户连接*/
		/*判定服务器socket是否改变*/
		if(FD_ISSET(sfd,&allfds)){
			/*接受客户连接*/
			fds[id]=accept(sfd,0,0);
			if(fds[id]==-1){
				printf("服务器崩溃!\n");
				/*关闭所有客户*/
				/*关闭服务器socket*/
				exit(-1);
			}
			printf("有客户连接!\n");
			id++;
		}	
		/*3.2.处理客户socket:接受数据，广播数据*/
		for(i=0;i<id;i++){
			/*循环判定那些客户socket有数据可以读取*/
			if(fds[i]!=-1 && FD_ISSET(fds[i],&allfds)){
				/*读取数据*/
				r=recv(fds[i],buf,sizeof(buf)-1,0);
				if(r<=0){
					printf("有客户退出!\n");
					close(fds[i]);
					fds[i]=-1;
					continue;
				}
				buf[r]=0;
				printf("聊天信息:%s",buf);
				/*广播数据*/
				for(j=0;j<id;j++){
					if(fds[j]!=-1){
						send(fds[j],buf,strlen(buf),0);
					}
				}
			}
		}
	}
}

