#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
extern int errno;
main()
{
	void *p=malloc(2000000000);
	if(!p) printf("�ڴ����ʧ��!\n");
	void *p1=malloc(2000000000);
	if(!p1){
		//printf("�ڴ����ʧ��!\n");
		//printf("%d:%s\n",errno,strerror(errno));
		//perror("�ڴ�������ԭ��");
		printf("�ڴ��������ԭ��:%m\n");
	}
	printf("%.*2$lf\n",88888.88888,4);
	
	double f;
	scanf("%lf",&f);
	printf("%f\n",f);
	int n;
	/*printf�Ѿ�������ַ�����*/
	printf("Hello%n\n",&n);
	printf("���������:%d\n",n);
	/*
	�����һ���ж����߼�©��
	if(errno) printf("�ڴ�������!\n");
	*/
	
}
