#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
	int fd;
	int r;
	char name[32];
	
	fd=open("wtmpx",O_RDWR);
	
	lseek(fd,100,SEEK_SET);
	pread(fd,name,32,0);
	printf("name:%s\n",name);
	
	r=lseek(fd,0,SEEK_CUR);/*���ص�ǰ�ļ���дָ��λ��*/
	printf("%d\n",r);
	
	close(fd);
	return 0;
}
