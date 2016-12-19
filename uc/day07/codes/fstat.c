#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
int main()
{
	int fd;
	struct stat st;
	//1.打开文件
	fd=open("a.txt",O_RDWR);
	if(fd==-1) printf("%m\n"),exit(-1);
	
	//2.获取文件状态
	fstat(fd,&st);
	
	//3.打印文件状态
	printf("文件权限:%o\n",st.st_mode);
	printf("文件大小:%d\n",st.st_size);
	//4.关闭文件
	close(fd);
	return 0;
}
