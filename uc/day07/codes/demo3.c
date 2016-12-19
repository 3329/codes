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
	/*打开文件*/
	fd=open("wtmpx",O_RDONLY);
	if(fd==-1) printf("%m\n"),exit(-1);
	/*获取文件大小*/
	fstat(fd,&st);
	/*计算记录条数*/
	recordnum=st.st_size/372;
	/*打印*/
	printf("wtmpx记录条数:%d\n",recordnum);
	/*关闭文件*/
	close(fd);
	return 0;
}
