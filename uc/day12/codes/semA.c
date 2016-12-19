#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
/*һ���ڳ����ж��壬��Ҫָ��ϵͳͷ�ļ�*/
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
	/*1.�����ź���ipcs -s*/
	key=ftok(".",100);
	if(key==-1) printf("ftok:%m\n"),exit(-1);
	
	semid=semget(key,1/*�ź����������*/,
							 IPC_CREAT|IPC_EXCL|0666);
	if(semid==-1) printf("semget:%m\n"),exit(-1);
	printf("key=0x%x,id=%d\n",key,semid);
	/*2.��ʼ���ź���*/
	union semun v;
	v.val=2;/*�ź�����ֵ����>=0*/
	semctl(semid,0,/*�ź����������±�*/
			SETVAL,v);/*���ĸ��������û�����������,*/
	
	/*3.���ź������У�����:����*/
	/*���������*/
	
	struct sembuf minusop;//[2];
	
	minusop.sem_num=0;/*�������ź��������±�*/
	minusop.sem_op=-1;/*�����ź����ķ�ʽ*/
	minusop.sem_flg=0;/*SEM_UNDO,IPC_NOWAIT*/
	
	//minusop[1].sem_num=0;/*�������ź��������±�*/
	//minusop[1].sem_op=-1;/*�����ź����ķ�ʽ*/
	//minusop[1].sem_flg=0;/*SEM_UNDO,IPC_NOWAIT*/
											 
	while(1){		
		printf("�ȴ�....\n");
		semop(semid,&minusop,1/*�ź�����������*/);
		printf("����\n");
	}	
	/*4.ɾ���ź���*/
	semctl(semid,0,IPC_RMID);/*�ڶ���������IPC_RMID������*/
	
}
