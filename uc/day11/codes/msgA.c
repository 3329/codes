#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

struct msg{
	long ltype;
	char data[40];
};
main()
{
	key_t key;
	int msgid;
	/*����key*/
	key=ftok(".",88);
	/*�����������*/
	msgid=msgget(key,IPC_CREAT|IPC_EXCL|0666);
	
	/*ѭ����ȡ��Ϣ*/
	struct msg q;
	while(1){
		msgrcv(msgid,&q,sizeof(q.data),1,0);
		printf("::%s\n",q.data);
	}
	
	/*ɾ���������*/
	msgctl(msgid,IPC_RMID,0);
}
