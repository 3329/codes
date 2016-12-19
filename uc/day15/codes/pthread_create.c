#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
/*1.定义线程代码函数*/
void * run(void *data){
	while(1)
		printf("我是线程!\n");
}
void * run2(void *data){
	while(1)
		printf("我是线程--2!\n");
}
main()
{
	/*2.定义线程ID*/
	pthread_t tid;
	pthread_t tid2;		
	/*3.创建线程*/
	pthread_create(&tid,NULL,run,NULL);
	pthread_create(&tid2,NULL,run2,NULL);
	while(1){
		printf("我是主线程----Main!\n");
	}
	pthread_join(tid,(void**)NULL);
	pthread_join(tid2,(void**)NULL);
}
