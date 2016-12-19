#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>  
int main()
{
	/*1.加载动态库*/
	void *h=dlopen("libku.so",RTLD_NOW);
	if(!h) printf("加载失败!\n"),exit(-1);
	
	/*2.查找函数*/
	int (*pinput)(const char*)=
			(int(*)(const char *))dlsym(h,"InputInt");
	if(!pinput) printf("InputInt函数没有找到!\n"),exit(-1);
	
	int(*pisprimer)(int)=dlsym(h,"IsPrimer");
	if(!pisprimer) printf("IsPrimer函数没有找到!\n"),exit(-1);
	
	/*3.调用函数*/
	int a=pinput("输入一个整数:");
	if(pisprimer(a)){
		printf("%d是素数!\n",a);
	}
	else{
		printf("%d是和数!\n",a);
	}
	/*4.关闭动态库*/
	dlclose(h);
	return 0;
}
