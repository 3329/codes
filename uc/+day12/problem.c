#include <stdio.h>
#include <pthread.h>
//1.
pthread_mutex_t m;
int a=0,b=0;
void display()
{
	//3
	
}
void *r1()
{
	while(1)
	{
		pthread_mutex_lock(&m);	
		a++;
		b++;		
		if(a!=b)
		{
			printf("%d!=%d\n",a,b);
			a=b=0;
		}
		pthread_mutex_unlock(&m);	
	}
}

void *r2()
{
	while(1)
	{
	
		pthread_mutex_lock(&m);	
		a++;
		b++;
		
		if(a!=b)
		{
			pthread_mutex_unlock(&m);
			printf("%d!=%d\n",a,b);
			a=b=0;
		}
		
	}
}
main()
{
	pthread_t t1,t2;
	//2
	pthread_mutex_init(&m,0);
	pthread_create(&t1,0,r1,0);
	pthread_create(&t2,0,r2,0);
	pthread_join(t1,(void**)0);
	pthread_join(t2,(void**)0);
	//4.
	pthread_mutex_destroy(&m);
}

