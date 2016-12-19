#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
main()
{
	int fd;
	struct sockaddr_in addr;
	char szreq[1024];/*请求数据*/
	int r;
	char buf[4096];/*接受服务器相应的数据*/
	struct hostent *ent;
	in_addr_t nip;
	char *szip;
	struct in_addr sip;
	
	ent=gethostbyname("www.baidu.com");
	nip=*((in_addr_t*)ent->h_addr);
	sip.s_addr=nip;
	szip=inet_ntoa(sip);
	printf("================\n");
	printf("%s\n",szip);
	printf("================\n");
	
	/*建立socket*/
	fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1) exit(-1);
	
	
	/*连接web服务器:192.168.0.72*/
	addr.sin_family=AF_INET;
	addr.sin_port=htons(80);
	//addr.sin_addr=sip;
	//inet_aton("192.168.0.72",&addr.sin_addr);
	inet_aton("119.75.218.77",&addr.sin_addr);
	/*memcpy(&addr.sin_addr.s_addr,&ent->h_addr,ent->h_length);*/
	
	r=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) exit(-1);
	/*构建HTTP请求*/
	sprintf(szreq,
					"GET /index.php HTTP/1.1\r\n"
							"Host: 119.75.218.77:80\r\n"
							"User-Agent: Tarena/1.0\r\n"
							"Accept: text/html,text/plain,image/png\r\n"
							"Accept-Language: zh-cn\r\n"
							"Accept-Charset: gb2312,utf-8\r\n"
							"Keep-Alive: 300\r\n"
							"Connection: keep-alive\r\n"
							"\r\n");
	printf("%s",szreq);		
	/*发送请求给服务器*/
	r=send(fd,szreq,strlen(szreq),0);
	if(r<=0) exit(-1);	
	/*接受服务器发送过来的数据*/
	//while(1){
		r=recv(fd,buf,sizeof(buf)-1,0);
	//	if(r<=0) break;		
		buf[r]=0;		
		printf("%s\n",buf);
	//	printf("==============================\n");
	//}
	close(fd);
	
}
