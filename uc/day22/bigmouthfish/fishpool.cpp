#include "fishpool.h"
#include <QPainter>
#include <cstdio>
void FishPool::paintEvent(QPaintEvent *e)
{
	QPainter p(this);
	f1->paint(&p);
	f2->paint(&p);		
}
void FishPool::keyPressEvent(QKeyEvent *e)
{
	int key=e->key();	
	switch(key)
	{
		case Qt::Key_Right:
			emit changeDir(0);
			emit move();
			break;
		case Qt::Key_Up:
			emit changeDir(90);
			emit move();
			break;
		case Qt::Key_Left:
			emit changeDir(180);
			emit move();
			break;
		case Qt::Key_Down:	
			emit changeDir(270);
			emit move();
			break;
	}
	repaint();
}

void FishPool::openmouth()
{
	f1->openMouth();
	f2->openMouth();
	this->repaint();
}
