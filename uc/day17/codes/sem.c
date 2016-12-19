#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
pthread_t t1,t2;
sem_t sem;
pthread_mutex_t m;
void *r1(void *d){	
	while(1){		
		pthread_mutex_lock(&m);
		sem_wait(&sem);
		printf("Ö´ÐÐ....\n");
		pthread_mutex_unlock(&m);
	}
}
void *r2(void *d){
	while(1){
		pthread_mutex_lock(&m);
		sleep(2);
		sem_post(&sem);
		pthread_mutex_unlock(&m);
	}
}

main()
{
	pthread_mutex_init(&m,0);
	sem_init(&sem,0,3);
	pthread_create(&t1,0,r1,0);
	pthread_create(&t2,0,r2,0);
	printf("t1=%u,t2=%u\n",t1,t2);
	pthread_join(t1,(void**)0);
	pthread_join(t2,(void**)0);
	sem_destroy(&sem);
	pthread_mutex_destroy(&m);
}
