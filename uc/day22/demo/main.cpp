#include "called.h"
#include "calling.h"
int main(){
	Calling calling;
	Called called;
	
	QObject::connect(
			&calling,SIGNAL(logsig()),//�ź�Դ�������ź�
			&called,SLOT(bizlog()));//�źŴ���Ĳ۶���
	
	calling.biz();	
	return 0;
}


