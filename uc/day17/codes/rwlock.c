#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
pthread_t t1,t2,t3;
pthread_rwlock_t  rw;
void *r1(void *d){
	while(1){
		pthread_rwlock_wrlock(&rw);
		printf("线程-1(写)\n");
		//sleep(1);
		pthread_rwlock_unlock(&rw);
		sched_yield();
	}
}
void *r2(void *d){
	while(1){
		pthread_rwlock_wrlock(&rw);
		printf("线程----2(写)\n");
		//sleep(1);
		pthread_rwlock_unlock(&rw);
		sched_yield();
	}
}
void *r3(void *d){
	while(1){
		pthread_rwlock_rdlock(&rw);
		printf("线程------3(读)\n");
		//sleep(1);
		pthread_rwlock_unlock(&rw);
		sched_yield();
	}
}

main()
{
	pthread_rwlock_init(&rw,0);
	pthread_create(&t1,0,r1,0);
	pthread_create(&t2,0,r2,0);
	pthread_create(&t3,0,r3,0);
	
	
	pthread_join(t1,(void**)0);
	pthread_join(t2,(void**)0);
	pthread_join(t3,(void**)0);
	pthread_rwlock_destroy(&rw);
}
