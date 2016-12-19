/*
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);
	//第三 个 参数默认指定为NULL，非NULL指定为参考地址信息,一般前面四个信息被指定就可以了！
void freeaddrinfo(struct addrinfo *res);
const char *gai_strerror(int errcode);

	struct addrinfo {
   	int     ai_flags;
      int     ai_family;
      int     ai_socktype;
      int     ai_protocol;
      size_t  ai_addrlen;
      struct sockaddr *ai_addr;
      char   *ai_canonname;
      struct addrinfo *ai_next;
       };

*/
#include <sys/types.h>
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
	struct addrinfo *info;
	/*下面前面两个参数不能同时为NULL*/
	int r=getaddrinfo(NULL/*"dev.louis.com"*/, /*NULL*/"webcache",NULL,&info);
	if(r==0)
	{	
		printf("%s\n",inet_ntoa(((struct sockaddr_in*)(info->ai_addr))->sin_addr));
	}
	else
	{
		printf("getaddrinfo error!\n");
	}
	
}
