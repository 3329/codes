#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
/*
shmctl��ѯ�����ڴ��״̬
ɾ�������ڴ�
*/
main()
{
	/*�õ�key*/
	key_t key=ftok(".",100);
	/*�õ�ID*/
	int shmid=shmget(key,4,0);
	/*��ѯ״̬*/
	struct shmid_ds st;
	shmctl(shmid,IPC_STAT,&st);	
	/*���״̬*/
	printf("������ID��%u\n",st.shm_perm.uid);
	printf("��С��%d\n",st.shm_segsz);
	printf("��������%d\n",st.shm_nattch);
	
	/*ɾ��*/
	shmctl(shmid,IPC_RMID,NULL);
}
