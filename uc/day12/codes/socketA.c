#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/un.h>
main(){
	int fd;
	/*1.����socket��������*/
	fd=socket(AF_FILE,SOCK_DGRAM,0);
	if(fd==-1) printf("socket:%m\n"),exit(-1);  
	printf("socket OK!\n");
	
	/*2.����ͨ�ŵ�ַ*/
	struct sockaddr_un addr={0};/*socket�ļ�ͨ�ŵĵ�ַ*/
	addr.sun_family=AF_FILE;/*��ַ�壺������socket�����Ĳ���һ��*/
	memcpy(addr.sun_path,"my.sock",strlen("my.sock")+1);
	
	/*3.��socket����������ͨ�ŵ�ַ��*/
	int r=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) printf("bind:%m\n"),close(fd),exit(-1);
	
	/*4.��socket�������Ŷ�����:read:recv:recvfrom*/
	char buf[256];
	while(1){
		bzero(buf,sizeof(buf));//��ʼ���ַ�����
		read(fd,buf,sizeof(buf));
		printf("::%s\n",buf);
	}
	/*5.�ر�socket��������*/
	close(fd);
	unlink("my.sock");
}

