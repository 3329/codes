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
	/*1.����socket*/
	cfd=socket(AF_INET,SOCK_STREAM,0);
	if(cfd==-1) exit(-1);
	printf("����socket�ɹ�!\n"); 
	/*2.���ӵ�������*/
	addr.sin_family=AF_INET;
	addr.sin_port=htons(7777);
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	r=connect(cfd,(struct sockaddr*)&addr,sizeof addr);
	if(r==-1) exit(-1);
	printf("���ӷ������ɹ�,��ʼ�����ļ�!\n");
	/*3.�����ļ�������*/	
	int len=strlen(file);
	printf("�����ļ�������:%d\n",len);
	r=send(cfd,&len,sizeof(len),0);
	/*4.�����ļ���*/
	printf("�����ļ���:%s\n",file);
	r=send(cfd,file,len,0);
	/*5.���ļ�*/
	ffd=open(file,O_RDONLY);	
	/*6.�õ��ļ�����*/
	struct stat st;
	fstat(ffd,&st);
	len=st.st_size;
	
	/*7.�����ļ�����*/
	printf("�����ļ�����:%d\n",len);
	r=send(cfd,&len,sizeof len,0);	
	while(1){
		/*8.ѭ�������ļ�����*/
		r=read(ffd,buf,sizeof buf);
		if(r==0) {
			printf("�������!\n");
			break;
		}
		if(r==-1) {
			printf("��ȡ�ļ�����!\n");
			break;
		}
		send(cfd,buf,r,0);
	}
	/*9.�ر��ļ���socket*/
	close(ffd);
	close(cfd);
}
