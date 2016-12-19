#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h> /*inet��ͨ�ŵ�ַ�ṹ��*/
#include <arpa/inet.h>   /*�ֽ���IP��ַ��ת������*/
main(){
	int fd;
	/*1.����socket��������*/
	fd=socket(AF_INET,SOCK_DGRAM,0);
	if(fd==-1) printf("socket:%m\n"),exit(-1);
	printf("socket OK!\n");
	
	/*2.����ͨ�ŵ�ַ*/
	struct sockaddr_in addr={0};
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	addr.sin_port=htons(9999);	
	
	/*3.��socket����������ͨ�ŵ�ַ��*/
	int r=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) printf("bind:%m\n"),close(fd),exit(-1);
	printf("bind OK!\n");
	
	/*4.��socket�������Ŷ�����:read:recv:recvfrom*/
	char buf[256];
	while(1){
		bzero(buf,sizeof(buf));
		read(fd,buf,sizeof(buf));
		printf("::%s\n",buf);
	}
	/*5.�ر�socket��������*/
	close(fd);
	//unlink("my.sock");
}

