#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

main()
{
	int fd;
	struct sockaddr_in addr;
	int r;
	/*1.����socket*/
	fd=socket(PF_INET,SOCK_STREAM,0);
	if(fd==-1) printf("socket:%m\n"),exit(-1);
	printf("����socket�ɹ�!\n");
	
	/*2.���ӵ�������*/
	addr.sin_family=PF_INET;
	addr.sin_port=htons(8888);
	inet_aton("192.168.180.67",&addr.sin_addr);
	r=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) printf("connect:%m\n"),close(fd),exit(-1);
	printf("�Ѿ����ӵ�������!\n");
	/*3.��������*/
	int i;
	for(i=0;i<20;i++){
		r=send(fd,"maomaoyu!",strlen("maomaoyu!"),0);
	}
	close(fd);
}
