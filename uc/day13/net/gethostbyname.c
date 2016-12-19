#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <netdb.h>
/*
#include <sys/utsname.h>

//得到主机名
int uname(struct utsname *buf);
              struct utsname {
                      char sysname[];
                      char nodename[];
                      char release[];
                      char version[];
                      char machine[];
              #ifdef _GNU_SOURCE
                      char domainname[];
              #endif
                                    };

//根据主机名获取主机IP地址,该函数读取的实际上是/etc/hosts文件中的数据或者DNS服务器上的信息
//系统管理中的网络工具也修改这个文件。

#include <netdb.h>
extern int h_errno;
struct hostent *gethostbyname(const char *name);


	struct hostent {
   	char    *h_name;        // official name of host
      char    **h_aliases;    // alias list
      int     h_addrtype;     // host address type,always AF_INET or AF_INET6
      int     h_length;       // length of address
      char    **h_addr_list;  // list of addresses
        }
   #define h_addr  h_addr_list[0]  // for backward compatibility

*/
main()
{
	struct hostent	*hptr;
	struct utsname	myname;

	if (uname(&myname) < 0)
		printf("uname：%m\n"),exit(1);
	
	printf("node name：%s\n",myname.nodename);
	//if ( (hptr = gethostbyname(myname.nodename)) == NULL)
	//if ( (hptr = gethostbyname("www.google.cn")) == NULL)//203.208.39.104
	if ( (hptr = gethostbyname("bbs.tarena.com.cn")) == NULL)//192.168.0.72	
		printf("gethostbyname:%m\n"),exit(-1);

	printf("host name：%s\n",hptr->h_name);	
	
	printf("地址类型：%d\n",hptr->h_addrtype);
	printf("地址长度：%d\n",hptr->h_length);	
	if(hptr->h_addr)
	{	
		//字节序采用的是little-end字节序
		printf("IP地址：%hhu.%hhu.%hhu.%hhu\n",hptr->h_addr[0],hptr->h_addr[1],hptr->h_addr[2],hptr->h_addr[3]);
	}
}
