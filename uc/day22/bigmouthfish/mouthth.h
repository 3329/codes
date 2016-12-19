#ifndef MOUTHTH_H
#define MOUTHTH_H
#include <QThread>
#include <QObject>
class MouthTh:public QThread
{
Q_OBJECT
signals:
	void openmouth();	
protected:
	void run();
public:
	bool isstop;
	MouthTh():isstop(false)
	{
	}
};	
#endif
