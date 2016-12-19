#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/un.h>
main()
{
	int serverfd;
	/*1.����������socket*/
	serverfd=socket(AF_FILE,SOCK_STREAM,0);
	if(serverfd==-1) printf("socket:%m\n"),exit(-1);
	printf("socket ok!\n");
	/*2.����һ��ͨ�ŵ�ַ*/
	struct sockaddr_un addr;
	addr.sun_family=AF_FILE;
	memcpy(addr.sun_path,"sock.dat",strlen("sock.dat")+1);
	/*3.��һ��ͨ�ŵ�ַ*/
	int r;
	r=bind(serverfd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) printf("bind:%m\n"),close(serverfd),exit(-1);
	printf("bind ok!\n");
	/*4.����������socket*/	
	r=listen(serverfd,10);
	if(r==-1) printf("listen:%m\n"),close(serverfd),exit(-1);
	printf("listen ok!\n");
	/*5.�Ӽ����б�õ��µ�������*/
	int fd;
	fd=accept(serverfd,NULL,NULL);
	if(fd==-1) printf("accept:%m\n"),close(serverfd),exit(-1);
	printf("�пͻ�����!\n");
	/*6.��ȡ����*/
	char buf[256];
	while(1){
		bzero(buf,sizeof(buf));
		read(fd,buf,sizeof(buf)-1);
		printf("::%s\n",buf);
	}
	/*7.�ر�����*/
	close(fd);
	/*8.�رշ�����socket*/
	close(serverfd);
}
