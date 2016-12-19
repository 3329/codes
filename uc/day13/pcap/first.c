#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pcap/pcap.h>
main()
{
	char *dev;
	char *net;
	char *mask;
	char errbuf[PCAP_ERRBUF_SIZE];
	/*
	查找可用的设备
	char *pcap_lookupdev(char *errbuf);
	int pcap_findalldevs(pcap_if_t **alldevsp, char *errbuf);

	*/
	dev=pcap_lookupdev(errbuf);
	if(dev==NULL)
	{
		printf("%s\n",errbuf);
		exit(-1);
	}
	printf("dev:%s\n",dev);

	bpf_u_int32 netp;
	bpf_u_int32 maskp;
	/*
	查找指定设备的网络参数：网络识别与网络掩码
	int pcap_lookupnet(const char *device, bpf_u_int32 *netp,bpf_u_int32 *maskp, char *errbuf);
	*/
	int r=pcap_lookupnet("eth0",&netp,&maskp,errbuf);
	if(r==-1)
	{
		printf("%s\n",errbuf);
		exit(-1);
	}
	printf("%d:%d\n",netp,maskp);
	struct in_addr  ddr;
	ddr.s_addr=maskp;
	printf("%s\n",inet_ntoa(ddr));


}
