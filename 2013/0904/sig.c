#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sched.h>
/*下面子进程的全局变量*/
int oldval=-1;/*存放上次找到的素数*/
int newval;/*存放本次找到的素数*/
sigset_t sigs;/*等待的屏蔽信号*/
sigset_t sigsus;/*挂起的屏蔽信号*/

int IsPrimer(int a){
	int i;
	for(i=2;i<a;i++){
		if(a%i==0){
			return 0;
		}
	}
	return 1;
}

/*子进程的信号处理*/
void  handle(int sig,siginfo_t *info,void *d){
	int val;	
	if(sig==35){
		val=info->si_int;
		if(val==-1){ /*素数查找完毕*/
			exit(0);/*直接结束子进程*/
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
		/*父进程:找素数*/
		int a=2;
		int b=100000;
		int i;
		int status;
		union sigval val;
		sched_yield();/*放弃当前执行机会，排到队尾*/
		sleep(1);
		for(i=a;i<b;i++){
			if(IsPrimer(i)){
				/*是素数:发信号给子进程35*/
				val.sival_int=i;
				sigqueue(pid,35,val);/*发送信号给子进程*/
				usleep(1000);
			}
		}
		/*素数查找完毕，通知子进程结束:35*/
		val.sival_int=-1;/*-1:素数查找*/
		sigqueue(pid,35,val);
		wait(&status);/*等待子进程结束*/
		printf("结束!\n");
		exit(0);/*父进程退出*/
	}
	else{
		/*子进程:找孪生素数*/
		struct sigaction  act={0};
		act.sa_sigaction=handle;
		sigemptyset(&act.sa_mask);
		sigfillset(&act.sa_mask);
		act.sa_flags=SA_SIGINFO;		
		sigaction(35,&act,NULL);/*信号处理*/

		sigemptyset(&sigs);
		sigemptyset(&sigsus);
		sigaddset(&sigs,2);
		sigaddset(&sigs,35);
				
		/*屏蔽2信号*/
		sigprocmask(SIG_BLOCK,&sigs,NULL);
		while(1){			
			sigsuspend(&sigsus);/*等待父进程发送的信号*/
		}
		sigprocmask(SIG_UNBLOCK,&sigs,NULL);
	}
}
