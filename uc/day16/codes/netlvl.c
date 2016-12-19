#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
main()
{
	int fd;
	char buf[4096];
	int r;
	struct ethhdr *hdr;
	fd=socket(AF_INET,SOCK_PACKET,htons(ETH_P_ALL));
	if(fd==-1) printf("socket:%m\n"),exit(-1);
	
	while(1){
		r=recv(fd,buf,sizeof(buf),0);
		if(r>0){
			printf("接受数据包长度:r=%d\n",r);
			hdr=(struct ethhdr*)buf;
			printf("%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX\n",
						 hdr->h_dest[0],
						 hdr->h_dest[1],
						 hdr->h_dest[2],
						 hdr->h_dest[3],
						 hdr->h_dest[4],
						 hdr->h_dest[5]);
		}
		
	}
}

