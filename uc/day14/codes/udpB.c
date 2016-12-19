#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
int sockfd;
struct sockaddr_in addr;
int r;
char buf[256];/*���ܼ����������ݣ��뷢������*/
char data[256];/*��������A�˵�����*/

void handle(int s){
	close(sockfd);
	exit(0);	
}

main()
{
	/*0.����ctrl+c�ź�*/
	signal(SIGINT,handle);
	/*1.����socket*/
	sockfd=socket(PF_INET,SOCK_DGRAM,0);
	if(sockfd==-1) printf("socket:%m\n"),exit(-1);
	printf("����socket�ɹ�!\n");
	
	/*2.����inetͨ�ŵ�ַ*/
	addr.sin_family=PF_INET;
	addr.sin_port=htons(11111);
	inet_aton("192.168.180.67",&addr.sin_addr);
	
	while(1){
		/*3.��������*/
		r=read(0,buf,sizeof(buf)-1);
		if(r<=0) break;
		buf[r]=0;
		/*4.��������*/
		sendto(sockfd,buf,strlen(buf),0,
					 (struct sockaddr*)&addr,sizeof(addr));
		/*5.����A����������*/
		r=recv(sockfd,data,sizeof(data)-1,0);
		if(r<=0) break;
		data[r]=0;
		/*6.��ӡ���ܵ�����*/
		printf("����A�˵�����:%s\n",data);
	}
	/*7.�ر�socket*/	
	close(sockfd);
}
