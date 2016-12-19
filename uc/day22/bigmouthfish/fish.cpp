#include "fish.h"
void Fish::changeDir(int d)
{
	this->dir=d;
}
void Fish::move()
{
	step++;
	step%=4;
	switch(dir)
	{
		case 0://right
			x+=1;
			break;
		case 90:
			y-=1;
			break;
		case 180:
			x-=1;
			break;
		case 270:
			y+=1;
			break;		
	}
}
void Fish::openMouth()
{
	if(isOpen)
	{
		mouth+=1;
		if(mouth>=30)
		{
			mouth=30;
			isOpen=!isOpen;
		}	
	}
	else
	{
		mouth-=1;
		if(mouth<=0)
		{
			mouth=0;
			isOpen=!isOpen;	
		}
	}
}

void Fish::paint(QPainter *p)
{
	//p->setPen(*color);
	/*p->drawPie(x,y,size,size,
		(dir+mouth)*16,(360-2*mouth)*16);
		*/
	p->drawPixmap(x,y,*role[dir/90][step]);
	//printf("(%d,%d) [%d,%d]\n",x,y,dir/90,step);
}
