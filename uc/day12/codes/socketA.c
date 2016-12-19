#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/un.h>
main(){
	int fd;
	/*1.创建socket描述符号*/
	fd=socket(AF_FILE,SOCK_DGRAM,0);
	if(fd==-1) printf("socket:%m\n"),exit(-1);  
	printf("socket OK!\n");
	
	/*2.构造通信地址*/
	struct sockaddr_un addr={0};/*socket文件通信的地址*/
	addr.sun_family=AF_FILE;/*地址族：必须与socket函数的参数一致*/
	memcpy(addr.sun_path,"my.sock",strlen("my.sock")+1);
	
	/*3.把socket描述符号与通信地址绑定*/
	int r=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) printf("bind:%m\n"),close(fd),exit(-1);
	
	/*4.从socket描述符号读数据:read:recv:recvfrom*/
	char buf[256];
	while(1){
		bzero(buf,sizeof(buf));//初始化字符数组
		read(fd,buf,sizeof(buf));
		printf("::%s\n",buf);
	}
	/*5.关闭socket描述符号*/
	close(fd);
	unlink("my.sock");
}

