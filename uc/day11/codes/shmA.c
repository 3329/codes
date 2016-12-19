/*���������ڴ�*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>
key_t key;
int shmid;
int *p;
void handle(int s){
	shmdt(p);
	exit(0);
}
main()
{
	signal(SIGINT,handle);
	/*1.ʹ���ļ�����KEY*/
	key=ftok(".",100);
	if(key==-1) printf("ftok:%m\n"),exit(-1);
	printf("key=0x%x\n",key);
	/*2.����һ�������ڴ�*/
	shmid=shmget(key,4,IPC_CREAT|IPC_EXCL|0666);
	if(shmid==-1) printf("shmget:%m\n"),exit(-1);
	printf("id=%d\n",shmid);
	/*3.���ع����ڴ�*/
	p=shmat(shmid,NULL,0);
	if(p==NULL || p==(void*)-1){
		printf("shmat:%m\n");
		exit(-1);
	}
	printf("����OK��\n");
	/*4.ʹ�ù����ڴ�*/
	while(1){
		printf("%d\n",*p);
		sleep(1);
	}
	/*5.ж�ع����ڴ�*/
	shmdt(p);
	/*6.ɾ�������ڴ�*/
	
}

