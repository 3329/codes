#include <unistd.h>
#include <stdio.h>
/*判定一个数是否素数*/
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
	
	pstart=sbrk(0);//保存首地址
	/*循环得到所有素数*/
	for(i=2;i<=b;i++)
	{
		if(IsPrimer(i)){
			p=sbrk(4);
			*p=i;
		}
	}
	p=sbrk(0);//素数存放的结束地址
	
	/*打印素数*/
	q=pstart;
	while(q!=p){
		printf("%d\n",*q);
		q++;
	}
	/*释放空间*/
	printf("素数个数:%d\n",p-pstart);
	brk(pstart);	
	//sbrk(-(p-pstart)*sizeof(int));
}
