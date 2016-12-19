#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/un.h>

main()
{
	int fd;
	struct sockaddr_un addr;
	int r;	
	/*1.����socket:socket*/
	fd=socket(AF_FILE,SOCK_DGRAM,0);
	if(fd==-1) printf("socket:%m\n"),exit(-1);
	printf("socket OK!\n");
	
	/*2.����ͨ�ŵ�ַ:struct sockaddr_un*/
	addr.sun_family=AF_FILE;
	memcpy(addr.sun_path,"my.sock",strlen("my.sock")+1);
	
	/*3.���ӵ�ͨ�ŵ�ַ:connect*/
	r=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) printf("connect:%m\n"),close(fd),exit(-1);
	printf("�ɹ����ӵ�socket�ļ�!\n");
	
	/*4.�������ݵ�Ŀ��:write*/
	while(1){
		write(fd,"����!",strlen("����!"));
		sleep(1);
	}
	
	/*5.�ر�socket:close*/
	close(fd);
}
