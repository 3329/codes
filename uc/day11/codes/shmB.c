#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <signal.h>
key_t key;
int shmid;
int i;
int *p;
void handle(int s)
{
	shmdt(p);
	exit(0);
}	
main()
{
	signal(SIGINT,handle);
	/*1����KEY*/
	key=ftok(".",100);
	if(key==-1) printf("ftok:%m\n"),exit(-1);
	printf("key=0x%x\n",key);
	/*2.����KEY�õ������ڴ�ID*/
	shmid=shmget(key,4,0);
	if(shmid==-1) printf("shmget:%m\n"),exit(-1);
	printf("id=%d\n",shmid);
	/*3.���ص������ڴ�*/
	p=shmat(shmid,0,0);
	/*4.д���ݵ������ڴ�*/
	i=0;
	while(1){
		i++;
		*p=i;
		sleep(1);
	}
	/*5.ж�ع����ڴ�*/
	shmdt(p);	
}

