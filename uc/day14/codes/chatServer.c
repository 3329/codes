#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/mman.h>

main()
{
	int *fds;/*������������ߵ�������������*/
	int count=0;/*�Ѿ����ӵ��û�����*/
	int sfd;/*������socket*/
	int r;/*��ŷ���ֵ*/	
	int id;
	fds=mmap(0,getpagesize(),PROT_READ|PROT_WRITE,
					MAP_ANONYMOUS|MAP_SHARED,0,0);
	for(id=0;id<getpagesize()/4;id++){
		fds[id]=-1;
	}
	/*1.����socket*/
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1) exit(-1);
	printf("������socket�����ɹ���\n");
	/*2.�󶨵�ַ*/
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(10000);
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	r=bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) exit(-1);
	printf("��ַ�ﶨ�ɹ�!\n");
	/*3.����*/
	r=listen(sfd,10);
	if(r==-1) exit(-1);
	printf("�����ɹ�!\n");
	while(1){	
		printf("���ĵȴ��ͻ�����.....\n");
		/*4.ѭ�����ܿͻ�����,�ѿͻ������������ű�������*/
		fds[count]=accept(sfd,0,0);
		if(fds[count]==-1){
			/*֪ͨ�����ӽ��̽���*/
			printf("ϵͳ����������������!\n");
			/*�ͷ�*/
			munmap(fds,getpagesize());
			exit(-1);
		}
		/*5.�����ӽ���*/
		printf("��������!\n");
		if(fork()){
			count++;
			continue;
		}
		else{
			char buf[256];	
			while(1){/*ÿ���ͻ����ݴ����ӽ���*/								
				/*5.1.ѭ�����ܿͻ���������Ϣ*/
				r=recv(fds[count],buf,sizeof(buf)-1,0);
				if(r<=0){
					printf("�����˳�!\n");
					close(fds[count]);	
					fds[count]=-1;				
					exit(-1);/*�˳��ӽ���*/
				}
				buf[r]=0;
				printf("������Ϣ:%s\n",buf);
				/*5.2.Ⱥ�����ݵ����пͻ�*/
				int i;
				for(i=0;i<getpagesize()/4;i++){
					if(fds[i]!=-1){
						r=send(fds[i],buf,sizeof(buf),0);
					}					
				}
			}
		}
	}
}


