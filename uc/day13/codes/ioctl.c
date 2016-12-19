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
	/*1.创建socket描述符号*/
	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1) printf("socket:%m\n"),exit(-1);
	
	/*2.使用ioctl获取需要的信息*/
	struct ifreq req[5]={0};/*存放接口的列表*/
	struct ifconf  conf;
	conf.ifc_len=sizeof(req); /*返回接口列表的长度*/
	conf.ifc_req=req; /*指向存放接口的数组指针*/
	
	ioctl(s,SIOCGIFCONF,&conf);
	/*得到conf的接口列表*/
	/*得到接口的个数*/
	int num=conf.ifc_len/sizeof(struct ifreq);
	printf("接口个数:%d\n",num);
		
	/*打印接口名*/
	int i;
	for(i=0;i<num;i++){
		//printf("接口%d:%s\n",i+1,req[i].ifr_name);
		printf("接口%d:%s\n",i+1,req[i].ifr_ifrn.ifrn_name);
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



