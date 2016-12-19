#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
sigset_t sigs;
pthread_t todd,teven;
void* runodd(void *d)
{
	int i=0;	
	int s;
	for(i=0;;i+=2)
	{		
		printf("%d\n",i);				
		sigwait(&sigs,&s);
				
	}
}

void* runeven(void *d)
{
	int i=0;
	int s;
	for(i=1;;i+=2)
	{
		printf("%d\n",i);
		sleep(1);				
		pthread_kill(todd,34);		
	}
}


main()
{	
	sigemptyset(&sigs);
	sigaddset(&sigs,34);	
	pthread_create(&todd,0,runodd,0);
	pthread_create(&teven,0,runeven,0);
	pthread_join(todd,(void**)0);
	pthread_join(teven,(void**)0);
	
}
