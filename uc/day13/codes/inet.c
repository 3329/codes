#include <stdio.h>
#include <arpa/inet.h>
main()
{
	/*��֪�ַ���IP��ַ*/
	char *ip="192.168.180.67";
	/*1.ת��������*/
	in_addr_t nip=inet_addr(ip);
	printf("%d\n",nip);
	printf("%d.%d.%d.%d\n",nip&255,
					nip>>8&255,nip>>16&255,nip>>24&255);
	/*2.ת���ɽṹ��*/
	struct in_addr sip;
	inet_aton(ip,&sip);
	printf("%d\n",sip);	
	/*3.�ѽṹ��ת�����ַ���*/
	printf("%s\n",inet_ntoa(sip));
	/*4.ȡ�������ʶ*/
	in_addr_t net;
	net=inet_netof(sip);
	printf("%d\n",net);
	printf("%d.%d.%d.%d\n",net&255,
				net>>8&255,net>>16&255,net>>24&255);
	
	/*5.������ʶ*/
	in_addr_t host;
	host=inet_lnaof(sip);
	printf("%d\n",host);
	/*6.�ϳ�IP�ڽṹ��*/
	sip=inet_makeaddr(net,host);	
	/*7.ת�����ַ���*/
	printf("%s\n",inet_ntoa(sip));
	
}
