#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>  
int main()
{
	/*1.���ض�̬��*/
	void *h=dlopen("libku.so",RTLD_NOW);
	if(!h) printf("����ʧ��!\n"),exit(-1);
	
	/*2.���Һ���*/
	int (*pinput)(const char*)=
			(int(*)(const char *))dlsym(h,"InputInt");
	if(!pinput) printf("InputInt����û���ҵ�!\n"),exit(-1);
	
	int(*pisprimer)(int)=dlsym(h,"IsPrimer");
	if(!pisprimer) printf("IsPrimer����û���ҵ�!\n"),exit(-1);
	
	/*3.���ú���*/
	int a=pinput("����һ������:");
	if(pisprimer(a)){
		printf("%d������!\n",a);
	}
	else{
		printf("%d�Ǻ���!\n",a);
	}
	/*4.�رն�̬��*/
	dlclose(h);
	return 0;
}
