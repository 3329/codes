#include <stdio.h>
#include <pthread.h>
#include <signal.h>
pthread_t t1,t2;
pthread_cond_t cond;//1.
pthread_mutex_t m;
void *r1(void* d)
{
	int s;
	while(1)
	{			
		pthread_cond_wait(&cond,&m);	
		printf("»î¶¯!\n");
	}
}
void *r2(void* d)
{
	while(1)
	{			
		pthread_cond_signal(&cond);
		pthread_cond_signal(&cond);
		pthread_cond_signal(&cond);
		sleep(10);
	}
}
main()
{
	pthread_mutex_init(&m,0);
	pthread_cond_init(&cond,0);//2
	pthread_create(&t1,0,r1,0);
	pthread_create(&t2,0,r2,0);
	pthread_join(t1,(void**)0);
	pthread_join(t2,(void**)0);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&m);
}
