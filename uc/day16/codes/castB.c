#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
/*�㲥���ݽ���*/
main()
{
	int fd;
	int val=1;/*��ַ�ظ���*/
	struct sockaddr_in addr;
	char buf[256];
	int r;
	fd=socket(AF_INET,SOCK_DGRAM,0);
	if(fd==-1) exit(-1);
	printf("����socket�ɹ�!\n");
	
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9999);
	addr.sin_addr.s_addr=inet_addr("192.168.180.255");
	/*���õ�ַ���ظ���ѡ��*/
	setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));//���ظ���
	
	r=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) exit(-1);
	printf("�󶨵�ַ�ɹ�!\n");
	
	while(1){
		r=recv(fd,buf,sizeof(buf)-1,0);
		if(r>0){
			buf[r]=0;
			printf("%s\n",buf);
		}
	}
	
	
	
	
}
