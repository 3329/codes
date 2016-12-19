#include <pthread.h>
#include <curses.h>
#include <math.h>
struct  AChar
{
	int x;
	int y;
	int speed;
	char a;
};
int stop=1;
pthread_t t[26];
pthread_t tid;
pthread_mutex_t m;
struct AChar  a[26];

void *run(void *d)
{	
	int id;
	static idx=-1;
	idx++;
	id=idx;
	while(stop)
	{
		pthread_mutex_lock(&m);
		//改变对象的y坐标
		a[id].y+=a[id].speed;
		if(a[id].y>=LINES)
		{
			a[id].y=rand()%(LINES/4);
		}
		pthread_mutex_unlock(&m);
		sched_yield();		
		usleep(100000);
	}
}
void * update(void *d)
{
	int i=0;
	while(stop)
	{
		erase();
		//绘制屏幕上
		for(i=0;i<26;i++)
		{	
			mvaddch(a[i].y,a[i].x,a[i].a);
		}
		//刷屏
		refresh();
		usleep(10000);
	}
	
}

main()
{
	int i;
	initscr();
	curs_set(0);
	noecho();
	keypad(stdscr,TRUE);
	for(i=0;i<26;i++)
	{
		a[i].x=rand()%COLS;
		a[i].y=rand()%(LINES/4);
		a[i].speed=1+rand()%3;
		a[i].a=65+rand()%26;
	}	
	pthread_mutex_init(&m,0);	
	pthread_create(&tid,0,update,0);
	for(i=0;i<26;i++)
	{
		//随机产生字母与位置		
		pthread_create(&t[i],0,run,0);
	}	
	getch();
	stop=0;
	for(i=0;i<26;i++)
	{
		//随机产生字母与位置		
		pthread_join(t[i],(void**)0);
	}
	pthread_join(tid,(void**)0);
	pthread_mutex_destroy(&m);
	endwin();	
}
