#include <unistd.h>
#include <stdio.h>
/*�ж�һ�����Ƿ�����*/
int IsPrimer(int a){
	int i;
	for(i=2;i<a;i++){
		if(a%i==0){
			return 0;
		}
	}
	return 1;
}

main()
{
	int a=2;
	int b=20;
	int i;
	int *pstart;
	int *p;
	int *q;
	
	pstart=sbrk(0);//�����׵�ַ
	/*ѭ���õ���������*/
	for(i=2;i<=b;i++)
	{
		if(IsPrimer(i)){
			p=sbrk(4);
			*p=i;
		}
	}
	p=sbrk(0);//������ŵĽ�����ַ
	
	/*��ӡ����*/
	q=pstart;
	while(q!=p){
		printf("%d\n",*q);
		q++;
	}
	/*�ͷſռ�*/
	printf("��������:%d\n",p-pstart);
	brk(pstart);	
	//sbrk(-(p-pstart)*sizeof(int));
}
