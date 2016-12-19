#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>

main()
{
	int s;
	/*1.����socket��������*/
	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1) printf("socket:%m\n"),exit(-1);
	
	/*2.ʹ��ioctl��ȡ��Ҫ����Ϣ*/
	struct ifreq req[5]={0};/*��Žӿڵ��б�*/
	struct ifconf  conf;
	conf.ifc_len=sizeof(req); /*���ؽӿ��б�ĳ���*/
	conf.ifc_req=req; /*ָ���Žӿڵ�����ָ��*/
	
	ioctl(s,SIOCGIFCONF,&conf);
	/*�õ�conf�Ľӿ��б�*/
	/*�õ��ӿڵĸ���*/
	int num=conf.ifc_len/sizeof(struct ifreq);
	printf("�ӿڸ���:%d\n",num);
		
	/*��ӡ�ӿ���*/
	int i;
	for(i=0;i<num;i++){
		//printf("�ӿ�%d:%s\n",i+1,req[i].ifr_name);
		printf("�ӿ�%d:%s\n",i+1,req[i].ifr_ifrn.ifrn_name);
	}
	printf("=========================\n");
	
	struct ifreq rip={0};
	memcpy(rip.ifr_name,"lo",strlen("lo")+1);
	
	ioctl(s,SIOCGIFADDR,&rip);
	struct sockaddr_in *ip=
				(struct sockaddr_in*)&(rip.ifr_addr);
	printf("::%s\n",inet_ntoa(ip->sin_addr));
	
	close(s);
}



