#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
/*
shmctl查询共享内存的状态
删除共享内存
*/
main()
{
	/*得到key*/
	key_t key=ftok(".",100);
	/*得到ID*/
	int shmid=shmget(key,4,0);
	/*查询状态*/
	struct shmid_ds st;
	shmctl(shmid,IPC_STAT,&st);	
	/*输出状态*/
	printf("创建者ID：%u\n",st.shm_perm.uid);
	printf("大小：%d\n",st.shm_segsz);
	printf("挂载数：%d\n",st.shm_nattch);
	
	/*删除*/
	shmctl(shmid,IPC_RMID,NULL);
}
