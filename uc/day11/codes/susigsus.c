#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <signal.h>

int oldnum=-1;
int newnum;
int *p=NULL;
int *stat=NULL;
int IsPrime(int a)
{
	int i;

	for(i=2;i<a;i++)
	{
		if(a%i==0){
			return 0;
		}
	}
	return 1;
}

void handler(int s,siginfo_t *info,void *d)
{
	int status;
	if(s==47){
		newnum=info->si_int;
		if(newnum-oldnum==2){
			printf("(%d,%d)\n",oldnum,newnum);
			*p=oldnum;
			*(++p)=newnum;
			p++;
		}
		oldnum=newnum;
	}
	else/*对于系统的46信号，作处理，这是子进程结束发过来的信号*/
	{
		wait(&status);
		printf("子进程结束：%d\n",status);
		brk(stat);/*释放空间*/
		exit(1);
	}
}

int main()
{
	if(fork())
	{
		/*父进程*/
		
		sigset_t sig;/*屏蔽的信号集*/
		sigset_t psig;/*新的屏蔽信号集*/
		struct  sigaction sc;
		sc.sa_handler=NULL;
		sc.sa_sigaction=handler;
		sigemptyset(&sc.sa_mask);
		sigfillset(&sc.sa_mask);
		sc.sa_flags=SA_SIGINFO;

		sigemptyset(&sig);
		sigemptyset(&psig);
		sigfillset(&sig);
		sigfillset(&psig);
		sigdelset(&psig,47);
		sigdelset(&psig,46);
		/*SIGCHLD子进程结束的信号也屏蔽了，在子进程通知结束之后，在结束*/
		stat=(int *)sbrk(4);/*分配空间*/
		p=stat;
		
		sigaction(47,&sc,NULL);
		sigaction(46,&sc,NULL);
		sigprocmask(SIG_BLOCK,&sig,NULL);
		while(1)
		{
			sigsuspend(&psig);
			/*新屏蔽信号，只处理47,46号信号，其他信号不处理，
			只有46，47这两个信号才作处理，
			虽然其他信号也能把它唤醒，但新的屏蔽又把屏蔽*/
		}
		sigprocmask(SIG_UNBLOCK,&sig,NULL);
		
	}else
	{
		/*子进程*/
		int s;
		int i;
		pid_t pid;
		union sigval val;
		printf("输入你要查找的数字：\n");
		scanf("%d",&s);
		pid=getppid();
		for(i=2;i<s;i++)
		{
			if(IsPrime(i))
			{
				val.sival_int=i;
				sigqueue(pid,47,val);
				usleep(100);
			}
		}
		/*结束发送一个信号*/
		val.sival_int=-1;
		sigqueue(pid,46,val);
		printf("子进程结束查找！\n");
	}

	return 0;
}
