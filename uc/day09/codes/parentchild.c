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
		printf("���ܵ��ź�:�ӽ����˳�!\n");
		//�ӽ��̻��ա��ӽ���δ����waitһֱ�ȴ�
		pid=wait(&status);
		printf("�����ӽ���!:%d:%d\n",pid,status>>8 &255);
		
		exit(0);//����������
	}
}
main()
{
	if(fork()==0){
		/*�ӽ���*/
		sleep(10);
		printf("�ӽ����˳�\n");
		exit(111);
	}
	else{
		signal(17,handle);
		/*������*/
		while(1);
	}		
}
