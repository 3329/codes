#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
extern int errno;
main()
{
	void *p=malloc(2000000000);
	if(!p) printf("内存分配失败!\n");
	void *p1=malloc(2000000000);
	if(!p1){
		//printf("内存分配失败!\n");
		//printf("%d:%s\n",errno,strerror(errno));
		//perror("内存分配错误原因");
		printf("内存分配错误的原因:%m\n");
	}
	printf("%.*2$lf\n",88888.88888,4);
	
	double f;
	scanf("%lf",&f);
	printf("%f\n",f);
	int n;
	/*printf已经输出的字符个数*/
	printf("Hello%n\n",&n);
	printf("输出个数是:%d\n",n);
	/*
	下面的一场判定有逻辑漏洞
	if(errno) printf("内存分配错误!\n");
	*/
	
}
