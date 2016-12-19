#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
pthread_t t1,t2;
sigset_t sigs;
void handle(int s)
{
	printf("信号!\n");
}
void*r1(void*d)
{	
	int s;
	while(1)
	{
		printf("线程－－1\n");
		sigwait(&sigs,&s);
		printf("接收到信号:%d!\n",s);
	}
}
void*r2(void*d)
{
	
	while(1)
	{
		printf("线程－－--2\n");
		sleep(2);
		pthread_kill(t1,SIGUSR1);
	}
}

main()
{
	sigemptyset(&sigs);
	//sigaddset(&sigs,SIGUSR1);
	sigfillset(&sigs);
	//signal(SIGUSR1,handle);
	pthread_create(&t1,0,r1,0);
	pthread_create(&t2,0,r2,0);
	
	pthread_join(t1,(void**)0);
	pthread_join(t2,(void**)0);
	
	
}
