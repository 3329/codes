#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>  
int main()
{
	typedef int(*INPUT)(const char*);
	typedef int(*IS)(int);
	
	/*1.���ض�̬��*/
	void *h=dlopen("libku.so",RTLD_NOW);
	if(!h) printf("����ʧ��!\n"),exit(-1);
	
	/*2.���Һ���*/
	INPUT pinput=(INPUT)dlsym(h,"InputInt");
	if(!pinput) printf("InputInt����û���ҵ�!\n"),exit(-1);
	
	IS pisprimer=dlsym(h,"IsPrimer");
	if(!pisprimer) printf("IsPrimer����û���ҵ�!\n"),exit(-1);
	
	/*3.���ú���*/
	int a=pinput("����һ������:");
me/tarena01/zz_UC[csd1204]/day6[5.22]/codes'

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
