#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
	int fd;
	char name[20];
	short age;
	float score;
	char sex;
	int r;/*存储读取的返回值*/
	/*打开文件*/
	fd=open("stu.dat",O_RDWR);
	if(fd==-1) printf("open:%m\n"),exit(-1);
	/*读取数据：判定文件结尾*/
	while(1){
me/tarena01/zz_UC[csd1204]/day6[5.22]/codes'

		r=read(fd,name,sizeof(name));
		if(r<=0) break;
		r=read(fd,&age,sizeof(age));
		r=read(fd,&score,sizeof(score));
		r=read(fd,&sex,sizeof(sex));
		printf("%s,%d,%.2f,%c\n",name,age,score,sex);
	}
	/*关闭文件*/
	close(fd);
	return 0;
}

