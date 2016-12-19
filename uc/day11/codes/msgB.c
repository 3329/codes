#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
struct msg{
long t;
char d[40];
};
main()
{
	key_t key;
	int msgid;
	key=ftok(".",88);
	
	msgid=msgget(key,0);
	
	int i=0;
	struct msg q;
	for(i=0;i<20;i++){
		q.t=1;
		sprintf(q.d,"Msg:%d",i);
		msgsnd(msgid,&q,sizeof(q.d),0);
	}
	for(i=0;i<20;i++){
		q.t=2;
		sprintf(q.d,"2Hello:%d",i);
		msgsnd(msgid,&q,sizeof(q.d),0);
	}
}
