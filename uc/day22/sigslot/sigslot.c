#include <stdio.h>
#include <unistd.h>
void bizlog(){
	printf("��־\n");
}

void bizlog2(){
	printf("��־2\n");
}

void bizlog3(){
	printf("��־3\n");
}


void biz(void (*mylog)()){
	int i=0;
	while(1){
		printf("����ҵ��!\n");
		sleep(1);
		i++;
		i%=5;
		if(i==4){
			mylog();
		}
	}	
}

main()
{
	biz(bizlog3);
}


