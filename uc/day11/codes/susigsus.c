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
	else/*����ϵͳ��46�źţ������������ӽ��̽������������ź�*/
	{
		wait(&status);
		printf("�ӽ��̽�����%d\n",status);
		brk(stat);/*�ͷſռ�*/
		exit(1);
	}
}

int main()
{
	if(fork())
	{
		/*������*/
		
		sigset_t sig;/*���ε��źż�*/
		sigset_t psig;/*�µ������źż�*/
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
		/*SIGCHLD�ӽ��̽������ź�Ҳ�����ˣ����ӽ���֪ͨ����֮���ڽ���*/
		stat=(int *)sbrk(4);/*����ռ�*/
		p=stat;
		
		sigaction(47,&sc,NULL);
		sigaction(46,&sc,NULL);
		sigprocmask(SIG_BLOCK,&sig,NULL);
		while(1)
		{
			sigsuspend(&psig);
			/*�������źţ�ֻ����47,46���źţ������źŲ�����
			ֻ��46��47�������źŲ�������
			��Ȼ�����ź�Ҳ�ܰ������ѣ����µ������ְ�����*/
		}
		sigprocmask(SIG_UNBLOCK,&sig,NULL);
		
	}else
	{
		/*�ӽ���*/
		int s;
		int i;
		pid_t pid;
		union sigval val;
		printf("������Ҫ���ҵ����֣�\n");
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
		/*��������һ���ź�*/
		val.sival_int=-1;
		sigqueue(pid,46,val);
		printf("�ӽ��̽������ң�\n");
	}

	return 0;
}
