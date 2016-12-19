#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sched.h>
/*�����ӽ��̵�ȫ�ֱ���*/
int oldval=-1;/*����ϴ��ҵ�������*/
int newval;/*��ű����ҵ�������*/
sigset_t sigs;/*�ȴ��������ź�*/
sigset_t sigsus;/*����������ź�*/

int IsPrimer(int a){
	int i;
	for(i=2;i<a;i++){
		if(a%i==0){
			return 0;
		}
	}
	return 1;
}

/*�ӽ��̵��źŴ���*/
void  handle(int sig,siginfo_t *info,void *d){
	int val;	
	if(sig==35){
		val=info->si_int;
		if(val==-1){ /*�����������*/
			exit(0);/*ֱ�ӽ����ӽ���*/
		}
		else{
			newval=val;			
			if(newval-oldval<=2){
				printf("(%d,%d)\n",oldval,newval);	
			}
			oldval=newval;
		}
	}
}

main()
{
	pid_t pid;
	if(pid=fork()){
		/*������:������*/
		int a=2;
		int b=10000;
		int i;
		int status;
		union sigval val;
		sched_yield();/*������ǰִ�л��ᣬ�ŵ���β*/
		sleep(1);
		for(i=a;i<b;i++){
			if(IsPrimer(i)){
				/*������:���źŸ��ӽ���35*/
				val.sival_int=i;
				sigqueue(pid,35,val);/*�����źŸ��ӽ���*/
				usleep(1000);
			}
		}
		/*����������ϣ�֪ͨ�ӽ��̽���:35*/
		val.sival_int=-1;/*-1:��������*/
		sigqueue(pid,35,val);
		wait(&status);/*�ȴ��ӽ��̽���*/
		printf("����!\n");
		exit(0);/*�������˳�*/
	}
	else{
		/*�ӽ���:����������*/
		struct sigaction  act={0};
		act.sa_sigaction=handle;
		sigemptyset(&act.sa_mask);
		sigfillset(&act.sa_mask);
		act.sa_flags=SA_SIGINFO;		
		sigaction(35,&act,NULL);/*�źŴ���*/

		sigemptyset(&sigs);
		sigemptyset(&sigsus);
		sigaddset(&sigs,2);
		sigaddset(&sigs,35);
				
		/*����2�ź�*/
		sigprocmask(SIG_BLOCK,&sigs,NULL);
		while(1){			
			sigsuspend(&sigsus);/*�ȴ������̷��͵��ź�*/
		}
		sigprocmask(SIG_UNBLOCK,&sigs,NULL);
	}
}

