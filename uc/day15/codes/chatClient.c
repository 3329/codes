#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
main()
{
	int fd;
	char buf[256];
	int r;
	fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1) exit(-1);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(10000);
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	r=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) exit(-1);
	
	if(fork()){ 
		while(1){
		/*���������뷢��*/
			r=read(0,buf,sizeof(buf)-1);
			if(r<=0) exit(0);
			buf[r]=0;
			r=send(fd,buf,strlen(buf),0);
			if(r<=0){
				close(fd);
				/*֪ͨ�ӽ���*/
				exit(-1);
			}
		}
	}
	else
	{
		/*���ݽ��ܣ�����ӡ*/
		while(1){
			r=recv(fd,buf,sizeof(buf)-1,0);
			if(r<=0) exit(-1);
			buf[r]=0;
			printf(">>%s\n",buf);
		}
	}
	
}

