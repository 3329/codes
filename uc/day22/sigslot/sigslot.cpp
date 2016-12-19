#include <stdio.h>
#include <unistd.h>
class ILog
{
public:
	virtual void bizlog()=0;	
};

class BizLog : public ILog{
public:	
	void bizlog(){
		printf("��־\n");
	}
};

class BizLog2: public ILog{
public:
	void bizlog(){
		printf("��־2\n");
	}
};

class BizSuperLog : public ILog{
public:
	void bizlog(){
		printf("������־2\n");
	}
};

class Biz{
public:
	ILog *log;
public:	
	void biz(){
		int i=0;
		while(1){
			printf("����ҵ��!\n");
			sleep(1);
			i++;
			i%=5;
			if(i==4){
				log->bizlog();
			}
		}
	}	
};

int main()
{
	BizSuperLog log;
	Biz  biz;
	biz.log=&log;
	
	biz.biz();
	return 0;	
}


