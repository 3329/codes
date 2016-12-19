#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
pthread_t t1,t2;
int isstop=0;
void handle(int s){
	printf("线程启动%u\n",pthread_self());
}


void *r1(void *d){
	signal(SIGUSR1,handle);
	while(1){
		while(isstop){
			printf("线程进入睡眠\n");
			pause();
			isstop=0;
		}
		//printf("线程--1\n");
	}
}
void *r2(void *d){
	while(1){
		sleep(2);
		isstop=1;
		sleep(5);
		//raise(SIGUSR1);
		pthread_kill(t1,SIGUSR1);
	}
}

main()
{
	pthread_create(&t1,0,r1,0);
	pthread_create(&t2,0,r2,0);
	printf("t1=%u,t2=%u\n",t1,t2);
	pthread_join(t1,(void**)0);
	pthread_join(t2,(void**)0);
}
