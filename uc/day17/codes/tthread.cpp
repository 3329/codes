#include "tthread.h"
#include <cstdio>
using namespace std;
void * CThread::s_run(void *d){
	CThread *th=(CThread *)d;
	th->run();
}
	
void CThread::join(){
	pthread_join(tid,(void**)0);
}
/*�̺߳���*/
void CThread::run(){
	/*��ʵ��*/
	while(true){
		printf("�߳�!\n");
	}
}
/*��ʼ�߳�:create*/
void CThread::start(){
	pthread_create(&tid,0,s_run,this);
}	