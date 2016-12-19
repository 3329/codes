#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
sem_t  sem;//
void *run(void*d)
{
	while(1)
	{
		//3.
		sem_wait(&sem);
		printf("½â³ý\n");
	}
}
main()
{
	pthread_t tid;
	//2
	sem_init(&sem,0,5);
	pthread_create(&tid,0,run,0);
	while(1)
	{
		//
		sleep(1);
		sem_post(&sem);
	}
}
