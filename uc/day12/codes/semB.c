#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>

main()
{
	key_t key;
	int semid;
	/*1.得到信号量*/
	key=ftok(".",100);
	semid=semget(key,1,0);
	
	/*2.加操作信号量*/
	struct sembuf addop;
	addop.sem_num=0;
	addop.sem_op=1;
	addop.sem_flg=SEM_UNDO;
	
	while(1){
		sleep(2);
		printf("对信号量+1\n");
		semop(semid,&addop,1);
	}
}
