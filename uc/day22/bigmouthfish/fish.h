#ifndef FISH_H
#define FISH_H
#include <QColor>
#include <QPainter>
#include <QObject>
#include <QPixmap>
#include <QBitmap>
class Fish : public QObject
{
Q_OBJECT	
private:
	int step;
	QPixmap *role[4][4];
	bool isOpen;
	int x;
	int y;
	int size;
	QColor *color;
	int mouth;
	int dir;//0:right,90:up,180:left,270:down
public:
	Fish(int x,int y):x(x),y(y),size(100),mouth(30),
		dir(0),isOpen(false),step(0)
	{
		color=new QColor(255,0,0);
		int i=0,j=0;
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				QString filename("./");
				filename+=QString::number(i)+QString::number(j)+".PNG";
				role[i][j]=new QPixmap(filename);
				QBitmap mask=role[i][j]->createMaskFromColor(QColor(255,255,255),Qt::MaskInColor);				
				role[i][j]->setMask(mask);
			}
		}
	}
	~Fish()
	{
		delete color;
	}
public slots:
	void changeDir(int d);
	void move();
	void openMouth();
public:
	void paint(QPainter *p);		
};
#endif
