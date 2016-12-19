#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/un.h>
#include <string.h>

main()
{
	/*1.建立客户socket*/
	int fd;
	fd=socket(AF_LOCAL,SOCK_STREAM,0);
	if(fd==-1) printf("socket:%m\n"),exit(-1);
	printf("scoket ok!\n");
	/*2.构造通信地址*/
	struct sockaddr_un addr;
	addr.sun_family=PF_UNIX;
	memcpy(addr.sun_path,"sock.dat",strlen("sock.dat")+1);
	/*3.连接到通信地址*/
	int r;
	r=connect(fd,(struct sockaddr*)&addr,sizeof addr);
	if(r==-1) printf("connect:%m\n"),close(fd),exit(-1);
	printf("connect ok!\n");
	/*4.发送数据*/
	while(1){
		sleep(1);
		write(fd,"Killer",6);
	}
	/*5.关闭连接*/
	close(fd);
}
