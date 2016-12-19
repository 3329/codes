/*
#include <netdb.h>
struct servent *getservent(void);
struct servent *getservbyname(const char *name, const char *proto);
struct servent *getservbyport(int port, const char *proto);
void setservent(int stayopen);
	参数为1，则在调用getservbyname() 与getservbyport()的时候不关闭文件
void endservent(void);

读取 /etc/services文件信息
	struct servent {
   	char    *s_name;        // official service name 
      char    **s_aliases;    // alias list 
      int     s_port;         // port number
      char    *s_proto;       // protocol to use
         }

*/
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

main()
{
	setservent(1);
	struct servent *serv;
	while((serv=getservent())!=NULL)
	{
		//printf("%s,%d,%s,%s\n",serv->s_name,serv->s_port,serv->s_proto,serv->s_aliases[0]==NULL?"":serv->s_aliases[0]);
	}
	endservent();
	serv=getservbyname("iqobject", NULL);//第一个参数必须为空，第二个参数为空默认为tcp
	if(serv!=NULL)
	{
		printf("%s,%d,%s,%s\n",serv->s_name,serv->s_port,serv->s_proto,serv->s_aliases[0]==NULL?"":serv->s_aliases[0]);
	}
	serv=getservbyport(htons(8080), "tcp");//第一个参数必须使用网络字节序
	if(serv!=NULL)
	{
		printf("%s,%d,%s,%s\n",serv->s_name,serv->s_port,serv->s_proto,serv->s_aliases[0]==NULL?"":serv->s_aliases[0]);
	}
}
