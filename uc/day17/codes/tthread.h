#ifndef TARENA_THREAD_H
#define TARENA_THREAD_H
#include <pthread.h>
class CThread 
{
private:
	pthread_t tid;
	/*�̺߳���*/
	static void * s_run(void *d);
public:
	/*join*/	
	void join();
	/*�̺߳���*/
	virtual void run();
	/*��ʼ�߳�:create*/
	void start();	
};
#endif
