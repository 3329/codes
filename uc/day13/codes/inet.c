#include <stdio.h>
#include <arpa/inet.h>
main()
{
	/*已知字符串IP地址*/
	char *ip="192.168.180.67";
	/*1.转换成整数*/
	in_addr_t nip=inet_addr(ip);
	printf("%d\n",nip);
	printf("%d.%d.%d.%d\n",nip&255,
					nip>>8&255,nip>>16&255,nip>>24&255);
	/*2.转换成结构体*/
	struct in_addr sip;
	inet_aton(ip,&sip);
	printf("%d\n",sip);	
	/*3.把结构体转换成字符串*/
	printf("%s\n",inet_ntoa(sip));
	/*4.取出网络标识*/
	in_addr_t net;
	net=inet_netof(sip);
	printf("%d\n",net);
	printf("%d.%d.%d.%d\n",net&255,
				net>>8&255,net>>16&255,net>>24&255);
	
	/*5.主机标识*/
	in_addr_t host;
	host=inet_lnaof(sip);
	printf("%d\n",host);
	/*6.合成IP在结构体*/
	sip=inet_makeaddr(net,host);	
	/*7.转换成字符串*/
	printf("%s\n",inet_ntoa(sip));
	
}
