#ifndef FISH_POOL_H
#define FISH_POOL_H
#include <QWidget>
#include <QPaintEvent>
#include "fish.h"
#include <QObject>
#include "mouthth.h"
class FishPool : public QWidget
{
Q_OBJECT	
signals:
	void changeDir(int dir);
	void move();
		
private:
	MouthTh t;
	Fish *f1;
	Fish *f2;
	
public:
	FishPool()
	{
		f1=new Fish(10,10);
		f2=new Fish(100,100);
		QObject::connect(
			&t,SIGNAL(openmouth()),
			this,SLOT(openmouth()));
		QObject::connect(this,SIGNAL(changeDir(int)),
										 f1,SLOT(changeDir(int)));
		QObject::connect(this,SIGNAL(move()),
										 f1,SLOT(move()));
		t.start();
		
		
		
	}	
	~FishPool()
	{
		delete f1;
		delete f2;
	}		
protected:
	void paintEvent(QPaintEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void closeEvent(QCloseEvent *e)
	{
		t.isstop=true;
		while(t.isRunning())
		{
		}
	}	
public slots:	
	void openmouth();
};	
#endif
