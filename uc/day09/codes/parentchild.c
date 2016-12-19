#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
void handle(int s)
{
	int status;
	pid_t pid;
	if(s==17){
		printf("接受到信号:子进程退出!\n");
		//子进程回收。子进程未结束wait一直等待
		pid=wait(&status);
		printf("回收子进程!:%d:%d\n",pid,status>>8 &255);
		
		exit(0);//结束父进程
	}
}
main()
{
	if(fork()==0){
		/*子进程*/
		sleep(10);
		printf("子进程退出\n");
		exit(111);
	}
	else{
		signal(17,handle);
		/*父进程*/
		while(1);
	}		
}
