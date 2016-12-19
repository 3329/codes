#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
	int fd;//文件描述符号
	int r;//读取返回值
	char name[32];//存放用户
	short len;//存放IP长度
	char ip[257];//存放IP
	int line=0;//读取记录行数
	/*1.打开文件*/
	fd=open("wtmpx",O_RDONLY);
	if(fd==-1) printf("open:%m\n"),exit(-1);
	/*2.循环读取*/
	while(1){
		/*3.定位每行记录的开始位置*/
		lseek(fd,line*372,SEEK_SET);
		/*4.读取用户名*/
		r=read(fd,name,32);
		/*5.判定记录是否结束*/
		if(r<=0) break;
		/*name[r]=0;*/
		/*5.定位*/
		lseek(fd,80,SEEK_CUR);
		/*6.读取IP长度*/
		read(fd,&len,sizeof(len));
		/*7.做字节序转换*/
		len=(len & 255)<<8 | (len >> 8 & 255);
		/*8.定位*/
		/*不需要定位*/
		/*9.读取IP地址*/
		read(fd,ip,sizeof(ip));
		/*10.对IP地址增加终止字符*/
		ip[len]='\0';
		/*11.输出*/
		printf("%s,%s\n",name,ip);
		line++;
	}
	//12.关闭文件
	close(fd);				 
	return 0;
}
