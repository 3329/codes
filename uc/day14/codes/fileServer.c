#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
/*接受文件*/
main()
{
	int sfd;/*服务器socket*/
	int cfd;/*连接者socket*/
	int ffd;/*新建的文件*/
	
	int len;/*文件名与文件的长度*/
	char buf[256];/*接受的文件内容*/
	
	struct sockaddr_in addr;/*服务器地址*/
	int r;/*存放临时返回变量*/
		
	/*1.建立socket*/
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1) exit(-1);
	printf("建立socket成功!\n");
	/*2.绑定通信地址*/
	addr.sin_family=AF_INET;
	addr.sin_port=htons(7777);
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	r=bind(sfd,(struct sockaddr*)&addr,sizeof addr);
	if(r==-1) exit(-1);
	printf("地址帮定成功!\n");	
	/*3.监听*/
	r=listen(sfd,10);
	if(r==-1) exit(-1);
	printf("监听成功，等待客户连接....\n");
	/*4.接受客户连接*/
	cfd=accept(sfd,NULL,NULL);
	if(cfd==-1) exit(-1);
	printf("有人连接,开始接受文件相关数据!\n");
	
	/*5.接受文件名长度*/
	r=recv(cfd,&len,sizeof len,MSG_WAITALL);
	if(r<=0) exit(-1);
	printf("文件名长度:%d\n",len);
	
	/*6.接受文件名,然后在主目录创建新的文件*/
	r=recv(cfd,buf,len,MSG_WAITALL);
	if(r<=0) exit(-1);
	buf[r]=0;
	printf("文件名:%s\n",buf);	
	
	char file[256];
	sprintf(file,"/home/soft02/%s",buf);
	
	ffd=open(file,O_RDWR|O_CREAT,0666);
	if(ffd==-1) exit(-1);
	printf("已经创建上传文件,开始数据传递...\n");
	/*7.接受文件长度*/
	r=recv(cfd,&len,sizeof len,MSG_WAITALL);
	if(r<=0) exit(-1);
	printf("文件长度:%d\n",len);
	while(1){
	/*8.接受文件内容,并把内容写入新创建的文件*/
		if(len>sizeof(buf)){
			r=recv(cfd,buf,sizeof(buf),MSG_WAITALL);
			if(r<=0) break;/*错误的情况*/
			write(ffd,buf,r);/*把数据写入文件*/
			len-=r;
		}
		else{
			r=recv(cfd,buf,len,MSG_WAITALL);
			if(r<=0) break;/*错误情况*/
			write(ffd,buf,r);/*数据写入文件*/
			printf("文件传递完毕!\n");
			break;/*结束*/
		}
	}	
	/*9.关闭文件，关闭连接*/
	printf("释放!\n");
	close(ffd);
	close(cfd);
	/*10.关闭服务器socket*/
	close(sfd);
}
