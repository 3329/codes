#include "mybutton.h"
#include <QPainter>
MyButton::MyButton(QWidget *parent)
	:QPushButton(parent){

}
void MyButton::paintEvent(QPaintEvent *e){
	/*���ư�ť����״*/
	QPainter  g(this);
	int w=width();
	int h=height();
	QPoint pTop(w/2,2);
	QPoint pBottom(w/2,h-2);
	QPoint pLeft(2,h/2);
	QPoint pRight(w-2,h/2);
	QColor cWhite(255,255,255);
	QColor cBlack(  0,  0,  0);
	QBrush bWhite(cWhite);
	QBrush bBlack(cBlack);
	QPen	 penWhite(bWhite,2);
	QPen	 penBlack(bBlack,2);
	
	
	/*��ɫ*/
	g.setPen(penWhite);
	g.drawLine(pTop,pLeft);
	g.drawLine(pTop,pRight);
	/*��ɫ*/
	g.setPen(penBlack);
	g.drawLine(pBottom,pLeft);
	g.drawLine(pBottom,pRight);
}
