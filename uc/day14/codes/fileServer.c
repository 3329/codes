#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
/*�����ļ�*/
main()
{
	int sfd;/*������socket*/
	int cfd;/*������socket*/
	int ffd;/*�½����ļ�*/
	
	int len;/*�ļ������ļ��ĳ���*/
	char buf[256];/*���ܵ��ļ�����*/
	
	struct sockaddr_in addr;/*��������ַ*/
	int r;/*�����ʱ���ر���*/
		
	/*1.����socket*/
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1) exit(-1);
	printf("����socket�ɹ�!\n");
	/*2.��ͨ�ŵ�ַ*/
	addr.sin_family=AF_INET;
	addr.sin_port=htons(7777);
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	r=bind(sfd,(struct sockaddr*)&addr,sizeof addr);
	if(r==-1) exit(-1);
	printf("��ַ�ﶨ�ɹ�!\n");	
	/*3.����*/
	r=listen(sfd,10);
	if(r==-1) exit(-1);
	printf("�����ɹ����ȴ��ͻ�����....\n");
	/*4.���ܿͻ�����*/
	cfd=accept(sfd,NULL,NULL);
	if(cfd==-1) exit(-1);
	printf("��������,��ʼ�����ļ��������!\n");
	
	/*5.�����ļ�������*/
	r=recv(cfd,&len,sizeof len,MSG_WAITALL);
	if(r<=0) exit(-1);
	printf("�ļ�������:%d\n",len);
	
	/*6.�����ļ���,Ȼ������Ŀ¼�����µ��ļ�*/
	r=recv(cfd,buf,len,MSG_WAITALL);
	if(r<=0) exit(-1);
	buf[r]=0;
	printf("�ļ���:%s\n",buf);	
	
	char file[256];
	sprintf(file,"/home/soft02/%s",buf);
	
	ffd=open(file,O_RDWR|O_CREAT,0666);
	if(ffd==-1) exit(-1);
	printf("�Ѿ������ϴ��ļ�,��ʼ���ݴ���...\n");
	/*7.�����ļ�����*/
	r=recv(cfd,&len,sizeof len,MSG_WAITALL);
	if(r<=0) exit(-1);
	printf("�ļ�����:%d\n",len);
	while(1){
	/*8.�����ļ�����,��������д���´������ļ�*/
		if(len>sizeof(buf)){
			r=recv(cfd,buf,sizeof(buf),MSG_WAITALL);
			if(r<=0) break;/*��������*/
			write(ffd,buf,r);/*������д���ļ�*/
			len-=r;
		}
		else{
			r=recv(cfd,buf,len,MSG_WAITALL);
			if(r<=0) break;/*�������*/
			write(ffd,buf,r);/*����д���ļ�*/
			printf("�ļ��������!\n");
			break;/*����*/
		}
	}	
	/*9.�ر��ļ����ر�����*/
	printf("�ͷ�!\n");
	close(ffd);
	close(cfd);
	/*10.�رշ�����socket*/
	close(sfd);
}
