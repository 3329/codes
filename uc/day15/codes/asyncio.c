#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
void handle(int s)
{
	char buf[256];
	int r;
	if(s==34){
		r=read(0,buf,sizeof(buf)-1);
		if(r>0){
			buf[r]=0;
			printf("::%s",buf);
		}
	}
}

main()
{
	/*����SIGIO�źţ��������źŴ����ж�ȡ����*/
	signal(34,handle);
	/*��0�����첽IO*/
	fcntl(0,F_SETFL,O_ASYNC);
	/*�����źŷ���Ŀ�����*/
	fcntl(0,F_SETOWN,getpid());
	/*���÷��͵��ź�*/
	/*-D_GNU_SOURCE*/
	fcntl(0,F_SETSIG,34);
	while(1);
}
