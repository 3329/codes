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
	int sfd;/*������socket*/
	int fds[4096];/*�洢���е����ӿͻ�socket:-1��ʾ����*/
	int id;/*�Ѿ����ӵ������*/
	fd_set allfds;/*�����ӵ��������ţ�ͬʱ�����Ѿ��ı����������*/
	int maxfd;/*�����������*/
	char buf[256];/*��ʱ���ÿ���ͻ�������*/
	int r;/*��ʱ��ź�������ֵ*/
	struct sockaddr_in addr;/*������ͨ�ŵ�ַ*/
	int i,j;
	/*0.��ʼ������*/
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
	/*1.���������� socket,�ﶨ��ַ������*/
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1) exit(-1);
	printf("������socket�����ɹ�!\n"); 
	
	r=bind(sfd,(struct sockaddr*)&addr,sizeof addr);
	if(r==-1) exit(-1);
	printf("�󶨳ɹ�!\n");
	
	r=listen(sfd,10);
	if(r==-1) exit(-1);
	printf("�����ɹ�!\n");
	
	while(1){
		/*2.��ʼ��Ҫ�����������(����������socket��ͻ�socket)*/
		FD_ZERO(&allfds);
		maxfd=-1;
		/*2.1.�ѷ�����socket������Ӽ���*/
		FD_SET(sfd,&allfds);
		maxfd=maxfd>=sfd?maxfd:sfd;
		/*2.2.�ѿͻ�socket������Ӽ���*/
		for(i=0;i<id;i++){
			if(fds[i]!=-1){
				FD_SET(fds[i],&allfds);
				maxfd=maxfd>=fds[i]?maxfd:fds[i];
			}
		}
		/*2.3.��ʼ���*/
		r=select(maxfd+1,&allfds,0,0,0);
		if(r==-1) {
			printf("ϵͳ����!\n");
			/*�ر����пͻ�*/
			for(i=0;i<id;i++){
				if(fds[i]!=-1){
					close(fds[i]);
					fds[i]=-1;
				}
			}
			/*�رշ�����socket*/
			close(sfd);
			/*�˳�*/
			exit(-1);
		}
		/*3.����ı����������*/
		/*3.1.���������socket:�����¿ͻ�����*/
		/*�ж�������socket�Ƿ�ı�*/
		if(FD_ISSET(sfd,&allfds)){
			/*���ܿͻ�����*/
			fds[id]=accept(sfd,0,0);
			if(fds[id]==-1){
				printf("����������!\n");
				/*�ر����пͻ�*/
				/*�رշ�����socket*/
				exit(-1);
			}
			printf("�пͻ�����!\n");
			id++;
		}	
		/*3.2.����ͻ�socket:�������ݣ��㲥����*/
		for(i=0;i<id;i++){
			/*ѭ���ж���Щ�ͻ�socket�����ݿ��Զ�ȡ*/
			if(fds[i]!=-1 && FD_ISSET(fds[i],&allfds)){
				/*��ȡ����*/
				r=recv(fds[i],buf,sizeof(buf)-1,0);
				if(r<=0){
					printf("�пͻ��˳�!\n");
					close(fds[i]);
					fds[i]=-1;
					continue;
				}
				buf[r]=0;
				printf("������Ϣ:%s",buf);
				/*�㲥����*/
				for(j=0;j<id;j++){
					if(fds[j]!=-1){
						send(fds[j],buf,strlen(buf),0);
					}
				}
			}
		}
	}
}

