#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pcap/pcap.h>
#include <netinet/ip.h>
//linux/if_ether.h 是以太网头定义。

	/*
	返回数据包捕获句柄
	pcap_t *pcap_open_live(const char *device,
		int snaplen,//捕获数据包大小
		int promisc,//是否对网络接口使用混杂模式
	int to_ms, char *errbuf);//超时时间

	把指定规则编译到过滤器
	int pcap_compile(pcap_t *p, //捕获句柄
		struct bpf_program *fp,	//返回编译的规则
		const char *str,// 规则，可以使用null
		int optimize, //控制优化结果
		bpf_u_int32 netmask);//捕获网络数据的网络掩码

	设置过滤规则
	int pcap_setfilter(pcap_t *p, struct bpf_program *fp);

	捕获数据包
	typedef void (*pcap_handler)(u_char *user, const struct pcap_pkthdr *h,const u_char *bytes);

	int pcap_loop(pcap_t *p, int cnt,pcap_handler callback, u_char *user);
	int pcap_dispatch(pcap_t *p,
		int cnt,//函数返回前的最大数据处理包，－1，0表示在缓冲中处理所有数据
		pcap_handler callback,//数据包回调处理函数
		u_char *user);//传递给回调函数的数据

	返回下一个数据包指针
	int pcap_next_ex(pcap_t *p, struct pcap_pkthdr **pkt_header,const u_char **pkt_data);
	const u_char *pcap_next(pcap_t *p, struct pcap_pkthdr *h);

	关闭网络资源
	void pcap_close(pcap_t *p);

	*/

	/*
	struct pcap_pkthdr {
        struct timeval ts;      // time stamp
        bpf_u_int32 caplen;     // length of portion present
        bpf_u_int32 len;        // length this packet (off wire)
	};
	*/
void handle(u_char *user, const struct pcap_pkthdr *h,const u_char *bytes)
{
	printf("有数据包，捕获长度:%d，实际长度:%d\n",h->caplen,h->len);
	if(h->len>14)
	{
		struct iphdr* hdr=(struct iphdr*)(bytes);
		printf("协议是:%d\n",hdr->protocol);
		struct in_addr ddr;
		ddr.s_addr=hdr->saddr;
		printf("来源地址:%s\n",inet_ntoa(ddr));
	}

}
main()
{
	pcap_t *h;
	char errbuf[PCAP_ERRBUF_SIZE];

	h=pcap_open_live("peth0",200,0,1000,errbuf);
	if(!h)
	{
		printf("::%s\n",errbuf);
		exit(-1);
	}

	int r;
	struct bpf_program fp;
	r=pcap_compile(h,&fp,0,1,0);
	if(r==-1)
	{
		printf("编译规则失败!\n");
		exit(-1);
	}

	r=pcap_setfilter(h,&fp);
	if(r==-1)
	{
		printf("设置过滤失败!\n");
		exit(-1);
	}

	r=pcap_loop(h,0,handle,0);
	if(r==-1)
	{
		printf("捕获数据包失败!\n");
		exit(-1);
	}
	printf("OK\n");
	pcap_close(h);
}
