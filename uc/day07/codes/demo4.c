#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
struct stu
{
	char name[20];
	short age;
	float score;
	char sex;
};
main()
{
	int fd;
	size_t len;//文件长度
	struct stu *p;//映射的文件内存地址
	struct stat st;
	struct stu *pend;
	int r;
	/*打开文件*/
	fd=open("stu.dat",O_RDWR);
	if(fd==-1){//文件不存在
		fd=open("stu.dat",O_RDWR|O_CREAT,0666);
		if(fd==-1){
			printf("文件打开或者创建失败:%m\n");
			exit(-1);
		}
	}
	/*取得文件大小*/
	r=fstat(fd,&st);
	if(r==-1){
		printf("获取文件大小失败:%m\n");
		close(fd);
		exit(-1);
	}
	len=st.st_size;
	/*修改文件大小为新的大小*/
	len+=3*sizeof(struct stu);
	r=ftruncate(fd,len);
	if(r==-1){
		printf("修改文件大小失败:%m\n");
		close(fd);
		exit(-1);
	}
	/*把文件映射成虚拟内存地址*/
	p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);	
	if(p==NULL || p==(void*)-1){
		printf("映射失败:%m\n");
		close(fd);
		exit(-1);
	}
	/*定位到文件末尾*/
	pend=p;
	pend+=(st.st_size/sizeof(struct stu));	 
	/*通过内存地址写入3条记录*/
	memset(pend,0,sizeof(struct stu));
	memcpy(pend->name,"tom",3);
	pend->age=18;
	pend->score=99.99f;
	pend->sex='m';
	
	pend++;
	memset(pend,0,sizeof(struct stu));
	memcpy(pend->name,"Jack",4);
	pend->age=19;
	pend->score=88.88f;
	pend->sex='m';
	
	pend++;
	memset(pend,0,sizeof(struct stu));
	memcpy(pend->name,"Rose",4);
	pend->age=20;
	pend->score=77.77f;
	pend->sex='f';	
	
	/*卸载映射*/
	munmap(p,len);
	/*关闭文件*/	
	close(fd);
}
