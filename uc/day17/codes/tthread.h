#ifndef TARENA_THREAD_H
#define TARENA_THREAD_H
#include <pthread.h>
class CThread 
{
private:
	pthread_t tid;
	/*线程函数*/
	static void * s_run(void *d);
public:
	/*join*/	
	void join();
	/*线程函数*/
	virtual void run();
	/*开始线程:create*/
	void start();	
};
#endif
