#include <stdio.h>
#include <netdb.h>
main()
{
	struct hostent *ent; 
	/*1.��/etc/hosts�ļ�����DNS*/
	sethostent(1);
	/*2.ѭ����ȡ/etc/hosts�ļ�*/
	while(ent=gethostent())
	{
		printf("%s,\n%d,\n%d,\n%d.%d.%d.%d\n",ent->h_name,
										ent->h_addrtype,
										ent->h_length,
										ent->h_addr[0],ent->h_addr[1],
										ent->h_addr[2],ent->h_addr[3]);
	}
	/*3.�ر�/etc/hosts�ļ�*/
	endhostent();
	printf("=========================\n");
	char *name="bbs.tarena.com.cn";
	struct hostent *bbsent;
	bbsent=gethostbyname(name);
	if(bbsent && bbsent->h_addr){
		printf("IP:%hhu.%hhu.%hhu.%hhu\n",bbsent->h_addr[0],
					 					bbsent->h_addr[1],
										bbsent->h_addr[2],
										bbsent->h_addr[3]);	
	}
}
