#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
pthread_t t1,t2;
sigset_t sigs;

void *r1(void *d){
	int s;	
	while(1){		
		printf("线程--1睡眠\n");
		sigwait(&sigs,&s);
		printf("线程--1觉醒\n");
		sleep(5);
	}
}
void *r2(void *d){
	while(1){
		sleep(3);
		pthread_kill(t1,SIGUSR1);
	}
}

main()
{
	sigemptyset(&sigs);
	sigfillset(&sigs);
	pthread_create(&t1,0,r1,0);
	pthread_create(&t2,0,r2,0);
	printf("t1=%u,t2=%u\n",t1,t2);
	pthread_join(t1,(void**)0);
	pthread_join(t2,(void**)0);
}
