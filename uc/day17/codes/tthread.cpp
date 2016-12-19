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
/*线程函数*/
void CThread::run(){
	/*空实现*/
	while(true){
		printf("线程!\n");
	}
}
/*开始线程:create*/
void CThread::start(){
	pthread_create(&tid,0,s_run,this);
}	