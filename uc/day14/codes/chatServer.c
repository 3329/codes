#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/mman.h>

main()
{
	int *fds;/*存放所有连接者的连接描述符号*/
	int count=0;/*已经连接的用户个数*/
	int sfd;/*服务器socket*/
	int r;/*存放返回值*/	
	int id;
	fds=mmap(0,getpagesize(),PROT_READ|PROT_WRITE,
					MAP_ANONYMOUS|MAP_SHARED,0,0);
	for(id=0;id<getpagesize()/4;id++){
		fds[id]=-1;
	}
	/*1.建立socket*/
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1) exit(-1);
	printf("服务器socket创建成功！\n");
	/*2.绑定地址*/
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(10000);
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	r=bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) exit(-1);
	printf("地址帮定成功!\n");
	/*3.监听*/
	r=listen(sfd,10);
	if(r==-1) exit(-1);
	printf("监听成功!\n");
	while(1){	
		printf("耐心等待客户连接.....\n");
		/*4.循环接受客户连接,把客户连接描述符号保存起来*/
		fds[count]=accept(sfd,0,0);
		if(fds[count]==-1){
			/*通知所有子进程结束*/
			printf("系统崩溃！服务器结束!\n");
			/*释放*/
			munmap(fds,getpagesize());
			exit(-1);
		}
		/*5.建立子进程*/
		printf("有人连接!\n");
		if(fork()){
			count++;
			continue;
		}
		else{
			char buf[256];	
			while(1){/*每个客户数据处理子进程*/								
				/*5.1.循环接受客户的聊天信息*/
				r=recv(fds[count],buf,sizeof(buf)-1,0);
				if(r<=0){
					printf("有人退出!\n");
					close(fds[count]);	
					fds[count]=-1;				
					exit(-1);/*退出子进程*/
				}
				buf[r]=0;
				printf("聊天信息:%s\n",buf);
				/*5.2.群发数据到所有客户*/
				int i;
				for(i=0;i<getpagesize()/4;i++){
					if(fds[i]!=-1){
						r=send(fds[i],buf,sizeof(buf),0);
					}					
				}
			}
		}
	}
}


