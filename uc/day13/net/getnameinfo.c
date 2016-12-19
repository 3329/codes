/*
#include <sys/socket.h>
#include <netdb.h>

int getnameinfo(const struct sockaddr *sa, socklen_t salen,
					 char *host, size_t hostlen,
                char *serv, size_t servlen, int flags);
返回主机与服务信息, 是gethostbyaddr(3) 与 getservbyport(3)两个功能的封装 
最后一个参数的说明：
       NI_NOFQDN				如果设置，仅仅返回本地FQDN主机名部分
       NI_NUMERICHOST 		返回数字形式的主机名
       NI_NAMEREQD			如果没有查找到主机名，返回一个错误
       NI_NUMERICSERV		服务地址以数字形式返回
       NI_DGRAM				服务是UDP,其中有些少量端口512-514。

*/
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
main()
{
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("192.168.1.158");
	addr.sin_port=htons(8080);
	char host[20];
	char serv[20];
	memset(host,0,20);
	memset(serv,0,20);
	int r=getnameinfo((struct sockaddr*)&addr,sizeof addr,host,20,serv,20,0);
	printf("%s,%s\n",host,serv);
	
}
