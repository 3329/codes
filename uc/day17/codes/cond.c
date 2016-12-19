#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sched.h>
pthread_t t1,t2,t3;
pthread_mutex_t m;
pthread_cond_t cond;
/*等*/
void *r1(void *d){	
	while(1){		
		pthread_mutex_lock(&m);		
		pthread_cond_wait(&cond,&m);
		printf("线程－－1执行\n");
		pthread_mutex_unlock(&m);
		sched_yield();
	}
}
/*等*/
void *r2(void *d){
	while(1){
		pthread_mutex_lock(&m);	
		pthread_cond_wait(&cond,&m);
		printf("线程－－－－2执行\n");		
		pthread_mutex_unlock(&m);
		sched_yield();
	}
}
/*解除等*/
void *r3(void *d){
	while(1){
		pthread_mutex_lock(&m);	
		sleep(3);
		//pthread_cond_signal(&cond);		
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&m);
		sched_yield();
	}
}
main()
{
	pthread_cond_init(&cond,0);
	pthread_mutex_init(&m,0);
	
	pthread_create(&t1,0,r1,0);
	pthread_create(&t2,0,r2,0);
	pthread_create(&t3,0,r3,0);
	printf("t1=%u,t2=%u\n",t1,t2);
	pthread_join(t1,(void**)0);
	pthread_join(t2,(void**)0);	
	pthread_join(t3,(void**)0);
	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&cond);
}
