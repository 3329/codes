#include <curses.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
//ȫ�ֱ�����������
WINDOW *wtime,*wnumb;
pthread_t thnumb,thtime;
pthread_mutex_t m;
//�߳�1�������
void*runnumb(void *d)
{
	int num;
	while(1)
	{
		//ѭ������7λ�����
		num=rand()%10000000;
		pthread_mutex_lock(&m);
		//��ʾ
		mvwprintw(wnumb,1,2,"%07d",num);
		//ˢ��
		refresh();
		wrefresh(wnumb);
		pthread_mutex_unlock(&m);
		usleep(1);
	}
	return 0;
}
//�߳�2��ʱ��
void*runtime(void*d)
{	
	time_t tt;
	struct tm *t;
	while(1)
	{
		//ѭ��ȡʱ��
		tt=time(0);
		t=localtime(&tt);
		pthread_mutex_lock(&m);
		//��ʾ
		mvwprintw(wtime,1,1,"%02d:%02d:%02d",
			t->tm_hour,t->tm_min,t->tm_sec);
		//ˢ��
		refresh();
		wrefresh(wtime);
		pthread_mutex_unlock(&m);
		usleep(1);
	}
}	

main()
{
	//��ʼ��curses
	initscr();
	curs_set(0);
	noecho();
	keypad(stdscr,TRUE);
	wnumb=derwin(stdscr,3,11,
			(LINES-3)/2,(COLS-11)/2);
	wtime=derwin(stdscr,3,10,0,COLS-10);
	box(wnumb,0,0);
	box(wtime,0,0);
	refresh();
	wrefresh(wnumb);
	wrefresh(wtime);
	pthread_mutex_init(&m,0);//2
	//�����߳�1
	pthread_create(&thnumb,0,runnumb,0);
	//�����߳�2
	pthread_create(&thtime,0,runtime,0);
	//�ȴ�����
	//����
	getch();
	pthread_mutex_destroy(&m);//3
	delwin(wnumb);
	delwin(wtime);
	endwin();
}
