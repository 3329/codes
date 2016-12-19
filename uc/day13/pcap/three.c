/*
返回联路层类型
int pcap_datalink(pcap_t *p);
返回最大抓包长度
int pcap_snapshot(pcap_t *p);
返回当前捕获与丢失的包
int pcap_stats(pcap_t *p, struct pcap_stat *ps);
struct pcap_stat {
	u_int ps_recv; // number of packets received
	u_int ps_drop; // number of packets dropped
	u_int ps_ifdrop; // drops by interface XXX not yet supported
};

int pcap_major_version(pcap_t *);
int pcap_minor_version(pcap_t *);
*/