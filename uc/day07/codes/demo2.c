#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
static int a=9999;
int main()
{
	int fd;
	int b;
	int r;
	char filename[257];
	sprintf(filename,"/proc/%d/mem",getpid());
	
	fd=open(filename,O_RDWR);
	if(fd==-1) printf("%m\n"),exit(-1);
	lseek(fd,(off_t)&a,SEEK_SET);
	//r=pread(fd,&b,sizeof(int),&a);
	r=read(fd,&b,sizeof(int));
	if(r>0){
		printf("b=%d\n",b);
	}
	if(r==-1)
	{
		printf("error:%m\n");
	}
	if(r==0){
		printf("end\n");
	}
	b=8888;
	r=pwrite(fd,&b,sizeof(4),&a);
	if(r==-1) printf("%m\n");
	
	printf("a=%d\n",a);
	close(fd);
	
	return 0;
}
