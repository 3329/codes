#ifndef CALLING_H
#define CALLING_H
#include <QObject>

class Calling : public QObject
{
Q_OBJECT	
public:
	void biz();	
public:signals:
	void logsig();		
};
#endif
