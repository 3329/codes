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
int id=0;
struct sockaddr_in addr={0};

void *clienth(void *d){
	/*2.1.ѭ�����ܿͻ�����*/
	/*2.2.�㲥�ͻ�����*/
}

main()
{	
	int i;
	for(i=0;i<4096;i++){
		fds[i]=-1;
	}
	addr.sin_family=AF_INET;
	addr.sin_port=htons(10000);
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	/*1.1.����������socket*/
	/*1.2.��ͨ�ŵ�ַ*/
	/*1.3.����*/
	/*1.4.ѭ�����ܿͻ�����*/
	/*1.5.�������߳�*/
}

