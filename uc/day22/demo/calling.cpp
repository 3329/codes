#include "calling.h"
#include <cstdio>
void Calling::biz(){
	int i=0;
	while(true){
		printf("处理业务!\n");
		if(i==4){
			//调用日志记录方法
			emit logsig();
		}
		i++;
		i%=5;
		sleep(1);
	}
}
