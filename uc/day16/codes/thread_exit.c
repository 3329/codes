#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
/*2线程在5秒后终止1线程*/
pthread_t t1,t2;
//int i=0;
time_t starttime;
int b=0;

void *r1(void *d){
	while(1){
		//if(i==1)
		//{
		//	pthread_exit("exit!");
		//}
		pthread_testcancel();
		printf("线程-1\n");
		sched_yield();
	}
}
void *r2(void *d){
	starttime=time(0);
	while(1){
		if(time(0)-starttime>=5 && b==0 ){
			//i=1;
			pthread_cancel(t1);
			b=1;
		}
		printf("线程----2\n");
		sched_yield();
	}
}


main()
{
	pthread_create(&t1,0,r1,0);
	pthread_create(&t2,0,r2,0);
	
	pthread_join(t1,(void**)0);
	printf("线程1－----------退出!\n");
	pthread_join(t2,(void**)0);
}
