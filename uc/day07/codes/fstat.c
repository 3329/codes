#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
int main()
{
	int fd;
	struct stat st;
	//1.���ļ�
	fd=open("a.txt",O_RDWR);
	if(fd==-1) printf("%m\n"),exit(-1);
	
	//2.��ȡ�ļ�״̬
	fstat(fd,&st);
	
	//3.��ӡ�ļ�״̬
	printf("�ļ�Ȩ��:%o\n",st.st_mode);
	printf("�ļ���С:%d\n",st.st_size);
	//4.�ر��ļ�
	close(fd);
	return 0;
}
