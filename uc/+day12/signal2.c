#include <stdio.h>
#include <pthread.h>
#include <signal.h>
pthread_t t1,t2;
sigset_t sigs;
void *r1(void* d)
{
	int s;
	while(1)
	{		
		sigwait(&sigs,&s);	
		printf("»î¶¯!\n");
	}
}
void *r2(void* d)
{
	while(1)
	{		
		sleep(1);
		pthread_kill(t1,34);
	}
}
main()
{
	sigemptyset(&sigs);
	sigaddset(&sigs,34);
	pthread_create(&t1,0,r1,0);
	pthread_create(&t2,0,r2,0);
	pthread_join(t1,(void**)0);
	pthread_join(t2,(void**)0);
}
