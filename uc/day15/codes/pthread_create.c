#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
/*1.�����̴߳��뺯��*/
void * run(void *data){
	while(1)
		printf("�����߳�!\n");
}
void * run2(void *data){
	while(1)
		printf("�����߳�--2!\n");
}
main()
{
	/*2.�����߳�ID*/
	pthread_t tid;
	pthread_t tid2;		
	/*3.�����߳�*/
	pthread_create(&tid,NULL,run,NULL);
	pthread_create(&tid2,NULL,run2,NULL);
	while(1){
		printf("�������߳�----Main!\n");
	}
	pthread_join(tid,(void**)NULL);
	pthread_join(tid2,(void**)NULL);
}
