#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>

main()
{
	int r;
	int fd;
	
	int  data;
	/*�����ܵ��ļ�*/
	r=mkfifo("a.pipe",0666);
	if(r==-1) printf("mkfifo:%m\n"),exit(-1);
	/*�򿪹ܵ�*/
	fd=open("a.pipe",O_RDWR);
	if(fd==-1) printf("open:%m\n"),exit(-1);
	/*ѭ���ӹܵ���ȡ����*/
	while(1){
		r=read(fd,&data,sizeof(data));
		if(r<=0) break;
		printf("::%d\n",data);
	}
	/*�رչܵ�*/
	close(fd);
	/*ɾ���ܵ��ļ�*/
	unlink("a.pipe");
}

