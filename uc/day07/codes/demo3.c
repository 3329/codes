#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
int main()
{
	int fd;
	struct stat st;
	size_t recordnum;
	/*���ļ�*/
	fd=open("wtmpx",O_RDONLY);
	if(fd==-1) printf("%m\n"),exit(-1);
	/*��ȡ�ļ���С*/
	fstat(fd,&st);
	/*�����¼����*/
	recordnum=st.st_size/372;
	/*��ӡ*/
	printf("wtmpx��¼����:%d\n",recordnum);
	/*�ر��ļ�*/
	close(fd);
	return 0;
}
