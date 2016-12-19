#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex;

int a=0,b=0;
void display(){	
	a++;
	b++;
	//pthread_mutex_unlock(&mutex);
	if(a!=b){
		printf("%d!=%d\n",a,b);
		a=b=0;
	}
	//pthread_mutex_unlock(&mutex);
}

void *r1(void *d){
	while(1){
		pthread_mutex_lock(&mutex);
		display();
		pthread_mutex_unlock(&mutex);
	}
}
void *r2(void *d){
	while(1){
		pthread_mutex_lock(&mutex);
		display();
		pthread_mutex_unlock(&mutex);
	}
}
main()
{	
	pthread_t t1,t2;
	pthread_mutex_init(&mutex,0);
	pthread_create(&t1,0,r1,0);
	pthread_create(&t2,0,r2,0);
	
	pthread_join(t1,(void**)0);
	pthread_join(t2,(void**)0);
	pthread_mutex_destroy(&mutex);
}
