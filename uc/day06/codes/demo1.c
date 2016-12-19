#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int fd;
	char name[20];
	short age;
	float score;
	char sex;
	mode_t mode;/*保存系统默认权限屏蔽*/
	/*创建一个文件*/
	mode=umask(0000);
	fd=open("stu.dat",O_RDWR|O_CREAT|O_EXCL,00666);
	if(fd==-1){
		printf("open:%m\n");
		umask(mode);
		exit(-1);
	}
	printf("open ok!\n");
	
	/*写入第一条记录*/
	/*memset(name,0,sizeof(name));*/
	bzero(name,sizeof(name));
	memcpy(name,"tom",strlen("tom")+1);
	age=18;
	score=88.55f;
	sex='m';
	write(fd,name,sizeof(name));
	write(fd,&age,sizeof(age));
	write(fd,&score,sizeof(score));
	write(fd,&sex,sizeof(sex));
	/*写入第二条记录*/
	bzero(name,sizeof(name));
	memcpy(name,"rose",strlen("rose")+1);
	age=19;
	score=100.00f;
	sex='f';
	write(fd,name,sizeof(name));
	write(fd,&age,sizeof(age));
	write(fd,&score,sizeof(score));
	write(fd,&sex,sizeof(sex));
	/*写入第三条记录*/
	bzero(name,sizeof(name));
	memcpcd '/home/tarena01/zz_UC[csd1204]/day6[5.22]/codes[ex]'
cd '/home/tarena01/zz_UC[csd1204]/day6[5.22]/codes'
cd '/home/tarena01/zz_UC[csd1204]/day6[5.22]/codes[ex]'
cd '/home/tarena01/zz_UC[csd1204]/day6[5.22]/codes'
cd '/home/tarena01/zz_UC[csd1204]/day6[5.22]/codes[ex]'
cd '/home/tarena01/zz_UC[csd1204]/day6[5.22]/codes[ex]'
cd '/home/tarena01/zz_UC[csd1204]/day6[5.22]/codes'
y(name,"clinton",strlen("clinton")+1);
	age=73;
	score=60.55f;
	sex='m';
	write(fd,name,sizeof(name));
	write(fd,&age,sizeof(age));
	write(fd,&score,sizeof(score));
	write(fd,&sex,sizeof(sex));
	/*关闭文件*/
	close(fd);
	umask(mode);
	return 0;
}

