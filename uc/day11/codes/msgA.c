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
	/*产生key*/
	key=ftok(".",88);
	/*产生共享队列*/
	msgid=msgget(key,IPC_CREAT|IPC_EXCL|0666);
	
	/*循环读取消息*/
	struct msg q;
	while(1){
		msgrcv(msgid,&q,sizeof(q.data),1,0);
		printf("::%s\n",q.data);
	}
	
	/*删除共享队列*/
	msgctl(msgid,IPC_RMID,0);
}
