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
	int idx=*((int*)d);/*��¼��������λ��*/
	char buf[256];
	int r,i;
	while(1){
		/*2.1.ѭ�����ܿͻ�����*/
		r=recv(fds[idx],buf,sizeof(buf)-1,0);
		if(r<=0) {
			printf("�пͻ��˳�!\n");
			close(fds[idx]);
			fds[idx]=-1;
			break;
		}	
		buf[r]=0;
		printf("������Ϣ:%s",buf);
		/*2.2.�㲥�ͻ�����*/
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
	/*1.1.����������socket*/
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1) exit(-1);
	printf("����socket�ɹ�1\n");
	/*1.2.��ͨ�ŵ�ַ*/
	r=bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) exit(-1);
	printf("�󶨳ɹ�!\n"); 
	/*1.3.����*/
	r=listen(sfd,10);
	if(r==-1) exit(-1);
	printf("�����ɹ�!\n");
	while(1){
		/*1.4.ѭ�����ܿͻ�����*/
		fds[id]=accept(sfd,0,0);
		if(fds[id]==-1) break;
		/*1.5.�������߳�*/
		printf("�пͻ�����!\n");	
		int tmpid=id;	
		pthread_create(&ths[id],0,clienth,&tmpid);		
		id++;
	}
	/*�ر���������*/
	/*��ֹ�����߳�*/
	close(sfd);
	printf("ϵͳ������\n");
}




