#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h>
main()
{
	int cfd;
	int ffd;
	struct sockaddr_in addr;
	int r;
	char buf[256];
	char *file="udpA.c";
	/*1.建立socket*/
	cfd=socket(AF_INET,SOCK_STREAM,0);
	if(cfd==-1) exit(-1);
	printf("建立socket成功!\n"); 
	/*2.连接到服务器*/
	addr.sin_family=AF_INET;
	addr.sin_port=htons(7777);
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	r=connect(cfd,(struct sockaddr*)&addr,sizeof addr);
	if(r==-1) exit(-1);
	printf("连接服务器成功,开始传送文件!\n");
	/*3.传递文件名长度*/	
	int len=strlen(file);
	printf("发送文件名长度:%d\n",len);
	r=send(cfd,&len,sizeof(len),0);
	/*4.传递文件名*/
	printf("发送文件名:%s\n",file);
	r=send(cfd,file,len,0);
	/*5.打开文件*/
	ffd=open(file,O_RDONLY);	
	/*6.得到文件长度*/
	struct stat st;
	fstat(ffd,&st);
	len=st.st_size;
	
	/*7.发送文件长度*/
	printf("发送文件长度:%d\n",len);
	r=send(cfd,&len,sizeof len,0);	
	while(1){
		/*8.循环发送文件内容*/
		r=read(ffd,buf,sizeof buf);
		if(r==0) {
			printf("发送完毕!\n");
			break;
		}
		if(r==-1) {
			printf("读取文件问题!\n");
			break;
		}
		send(cfd,buf,r,0);
	}
	/*9.关闭文件与socket*/
	close(ffd);
	close(cfd);
}
