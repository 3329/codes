#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
/*一定在程序中定义，不要指望系统头文件*/
union semun {
	int val;/*GETVAL SETVAL*/
	struct semid_ds *buf;/*IPC_STAT*/
	unsigned short  *array;/*SETALL/GETALL*/ 
	struct seminfo  *__buf;/*IPC_INFO*/
};

main()
{
	key_t key;
	int semid;
	/*1.创建信号量ipcs -s*/
	key=ftok(".",100);
	if(key==-1) printf("ftok:%m\n"),exit(-1);
	
	semid=semget(key,1/*信号量数组个数*/,
							 IPC_CREAT|IPC_EXCL|0666);
	if(semid==-1) printf("semget:%m\n"),exit(-1);
	printf("key=0x%x,id=%d\n",key,semid);
	/*2.初始化信号量*/
	union semun v;
	v.val=2;/*信号量的值必须>=0*/
	semctl(semid,0,/*信号量的数组下标*/
			SETVAL,v);/*第四个参数是用户定义联合体,*/
	
	/*3.对信号量进行－操作:阻塞*/
	/*定义减操作*/
	
	struct sembuf minusop;//[2];
	
	minusop.sem_num=0;/*操作的信号量数组下标*/
	minusop.sem_op=-1;/*操作信号两的方式*/
	minusop.sem_flg=0;/*SEM_UNDO,IPC_NOWAIT*/
	
	//minusop[1].sem_num=0;/*操作的信号量数组下标*/
	//minusop[1].sem_op=-1;/*操作信号两的方式*/
	//minusop[1].sem_flg=0;/*SEM_UNDO,IPC_NOWAIT*/
											 
	while(1){		
		printf("等待....\n");
		semop(semid,&minusop,1/*信号量操作个数*/);
		printf("继续\n");
	}	
	/*4.删除信号量*/
	semctl(semid,0,IPC_RMID);/*第二个参数对IPC_RMID无意义*/
	
}
