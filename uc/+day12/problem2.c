#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_mutex_t m;
void handle(void *d)
{
	printf("退出后的调用!\n");
	pthread_mutex_unlock(&m);
}

void* runodd(void *d)
{
	int i=0;	
	for(i=1;;i+=2)
	{	
			
		pthread_cleanup_push(handle,0);
		pthread_mutex_lock(&m);
		printf("%d\n",i);		
		pthread_cleanup_pop(1);				
	}
}

void* runeven(void *d)
{
	int i=0;
	for(i=0;;i+=2)
	{
		pthread_cleanup_push(handle,0);
		pthread_mutex_lock(&m);		
		printf("%d\n",i);		
		pthread_cleanup_pop(1);
		
	}
}


main()
{
	pthread_t todd,teven;
	pthread_mutex_init(&m,0);
	pthread_create(&todd,0,runodd,0);
	pthread_create(&teven,0,runeven,0);
	sleep(5);
	pthread_cancel(todd);
	pthread_join(todd,(void**)0);
	pthread_join(teven,(void**)0);
	pthread_mutex_destroy(&m);
}
