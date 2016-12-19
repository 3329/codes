/*
 	struct hostent *gethostent(void);//读取一个结构
	void sethostent(int stayopen);//打开hosts文件
		 其中的参数表示是否保留网络打开，1表示保持连接使用TCP，0表示每次关闭连接使用UDP
		gethostbyaddr与gethostbyname都是通过这个函数使用的,。
   void endhostent(void);//关闭hosts文件

*/
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

main()
{
	//打开DNS服务器或者其他host文件
	sethostent(1);
	struct hostent*hptr;
	while((hptr=gethostent()))
	{
		printf("IP地址：%hhu.%hhu.%hhu.%hhu\n",hptr->h_addr[0],hptr->h_addr[1],hptr->h_addr[2],hptr->h_addr[3]);
	}
	endhostent();
}
