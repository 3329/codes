#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/un.h>
#include <string.h>

main()
{
	/*1.�����ͻ�socket*/
	int fd;
	fd=socket(AF_LOCAL,SOCK_STREAM,0);
	if(fd==-1) printf("socket:%m\n"),exit(-1);
	printf("scoket ok!\n");
	/*2.����ͨ�ŵ�ַ*/
	struct sockaddr_un addr;
	addr.sun_family=PF_UNIX;
	memcpy(addr.sun_path,"sock.dat",strlen("sock.dat")+1);
	/*3.���ӵ�ͨ�ŵ�ַ*/
	int r;
	r=connect(fd,(struct sockaddr*)&addr,sizeof addr);
	if(r==-1) printf("connect:%m\n"),close(fd),exit(-1);
	printf("connect ok!\n");
	/*4.��������*/
	while(1){
		sleep(1);
		write(fd,"Killer",6);
	}
	/*5.�ر�����*/
	close(fd);
}
