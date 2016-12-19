#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pcap/pcap.h>
#include <netinet/ip.h>
//linux/if_ether.h ����̫��ͷ���塣

	/*
	�������ݰ�������
	pcap_t *pcap_open_live(const char *device,
		int snaplen,//�������ݰ���С
		int promisc,//�Ƿ������ӿ�ʹ�û���ģʽ
	int to_ms, char *errbuf);//��ʱʱ��

	��ָ��������뵽������
	int pcap_compile(pcap_t *p, //������
		struct bpf_program *fp,	//���ر���Ĺ���
		const char *str,// ���򣬿���ʹ��null
		int optimize, //�����Ż����
		bpf_u_int32 netmask);//�����������ݵ���������

	���ù��˹���
	int pcap_setfilter(pcap_t *p, struct bpf_program *fp);

	�������ݰ�
	typedef void (*pcap_handler)(u_char *user, const struct pcap_pkthdr *h,const u_char *bytes);

	int pcap_loop(pcap_t *p, int cnt,pcap_handler callback, u_char *user);
	int pcap_dispatch(pcap_t *p,
		int cnt,//��������ǰ��������ݴ��������1��0��ʾ�ڻ����д�����������
		pcap_handler callback,//���ݰ��ص�������
		u_char *user);//���ݸ��ص�����������

	������һ�����ݰ�ָ��
	int pcap_next_ex(pcap_t *p, struct pcap_pkthdr **pkt_header,const u_char **pkt_data);
	const u_char *pcap_next(pcap_t *p, struct pcap_pkthdr *h);

	�ر�������Դ
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
	printf("�����ݰ������񳤶�:%d��ʵ�ʳ���:%d\n",h->caplen,h->len);
	if(h->len>14)
	{
		struct iphdr* hdr=(struct iphdr*)(bytes);
		printf("Э����:%d\n",hdr->protocol);
		struct in_addr ddr;
		ddr.s_addr=hdr->saddr;
		printf("��Դ��ַ:%s\n",inet_ntoa(ddr));
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
		printf("�������ʧ��!\n");
		exit(-1);
	}

	r=pcap_setfilter(h,&fp);
	if(r==-1)
	{
		printf("���ù���ʧ��!\n");
		exit(-1);
	}

	r=pcap_loop(h,0,handle,0);
	if(r==-1)
	{
		printf("�������ݰ�ʧ��!\n");
		exit(-1);
	}
	printf("OK\n");
	pcap_close(h);
}
