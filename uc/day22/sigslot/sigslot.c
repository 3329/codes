#include <stdio.h>
#include <unistd.h>
void bizlog(){
	printf("日志\n");
}

void bizlog2(){
	printf("日志2\n");
}

void bizlog3(){
	printf("日志3\n");
}


void biz(void (*mylog)()){
	int i=0;
	while(1){
		printf("处理业务!\n");
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


