#include "called.h"
#include "calling.h"
int main(){
	Calling calling;
	Called called;
	
	QObject::connect(
			&calling,SIGNAL(logsig()),//信号源发出的信号
			&called,SLOT(bizlog()));//信号处理的槽对象
	
	calling.biz();	
	return 0;
}


