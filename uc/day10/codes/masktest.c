#include <stdio.h>
#include <unistd.h>
#include <signal.h>
main()
{
	int sum=0;
	int i;
	sigset_t sigs;
	sigset_t psigs;
	sigset_t newsigs;
	
	sigemptyset(&psigs);
	sigemptyset(&sigs);
	sigfillset(&sigs);
	sigfillset(&newsigs);
	sigdelset(&newsigs,2);
	//sigaddset(&sigs,SIGINT);
	/*�ź�����*/
	sigprocmask(SIG_BLOCK,&sigs,NULL);
	for(i=0;i<10;i++){
		sum+=i;
		sleep(1);
		printf("^o^\n");
		sigpending(&psigs);
		if(sigismember(&psigs,2)){
			/*����źſ�ʼ�µ��ź�����*/
			//sigsuspend(&newsigs);			
			sigprocmask(SIG_UNBLOCK,&sigs,NULL);
			sigprocmask(SIG_BLOCK,&newsigs,NULL);
			//�����ж�
			sigprocmask(SIG_UNBLOCK,&newsigs,NULL);
			sigprocmask(SIG_BLOCK,&sigs,NULL);
		}
	}
	printf("sum=%d\n",sum);	
	/*����ź�����*/
	sigprocmask(SIG_UNBLOCK,&sigs,NULL);
	printf("��������!\n");
}
