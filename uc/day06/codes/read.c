#include <unistd.h>
#include <stdio.h>

int main()
{
	char buf[256];
	ssize_t r;
	r=read(0,buf,255);/*留一个字节放\0字符*/
	if(r==0) printf("读到结束符号!\n");
	if(r>0) {
		buf[r]=0;//为字符串加一个空字符
		printf("%s\n",buf);
	}
	if(r==-1){
		printf("读取错误!\n");
	}
	return 0;
}

