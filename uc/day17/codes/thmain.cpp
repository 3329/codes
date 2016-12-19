#include "tthread.h"
#include <cstdio>
#include <unistd.h>
using namespace std;
class Th1 : public CThread{
public:
	void run(){
		while(true){
			printf("线程--1\n");
		}
	}		
};


class Th2 : public CThread{
	public:
		void run(){
			while(true){
				printf("线程------2\n");
			}
		}		
};

int main()
{
	Th1 t1;
	Th2 t2;
	t1.start();
	t2.start();
	t1.join();
	t2.join();
	return 0;
}
