#include "calling.h"
#include <cstdio>
void Calling::biz(){
	int i=0;
	while(true){
		printf("����ҵ��!\n");
		if(i==4){
			//������־��¼����
			emit logsig();
		}
		i++;
		i%=5;
		sleep(1);
	}
}
