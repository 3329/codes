#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>

main()
{
	key_t key;
	int semid;
	/*1.�õ��ź���*/
	key=ftok(".",100);
	semid=semget(key,1,0);
	
	/*2.�Ӳ����ź���*/
	struct sembuf addop;
	addop.sem_num=0;
	addop.sem_op=1;
	addop.sem_flg=SEM_UNDO;
	
	while(1){
		sleep(2);
		printf("���ź���+1\n");
		semop(semid,&addop,1);
	}
}
