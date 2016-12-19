#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
void handle(int s)
{
	printf("定时器!\n");
}
main()
{
	signal(SIGALRM,handle);
	/*注册定时器*/
	struct itimerval val={0};
	val.it_interval.tv_sec=2;
	val.it_interval.tv_usec=0;
	
	val.it_value.tv_sec=0;
	val.it_value.tv_usec=1;
	
	setitimer(ITIMER_REAL,&val,NULL);
	
	while(1);
}

