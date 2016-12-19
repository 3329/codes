#include <curses.h>
#include <signal.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
WINDOW *wnumb,*wtime;
void ctrlchandle(int s){
	delwin(wtime);
	delwin(wnumb);
	endwin();
	exit(0);
}
void timehandle(int s){
	/*2.显示时间*/
	time_t tt;
	struct tm *t;
	tt=time(NULL);
	t=localtime(&tt);
	mvwprintw(wtime,1,1,"%02u:%02u:%02u",
					 t->tm_hour,t->tm_min,t->tm_sec);
	refresh();
	wrefresh(wtime);
	wrefresh(wnumb);
}

main()
{
	struct itimerval val={0};
	val.it_interval.tv_sec=1;
	val.it_value.tv_usec=1;
	signal(SIGALRM,timehandle);
	/*1.完成curses的初始化*/
	initscr();
	curs_set(0);
	wnumb=derwin(stdscr,3,9,(LINES-3)/2,(COLS-9)/2);
	wtime=derwin(stdscr,3,10,0,COLS-10);
	box(wnumb,0,0);
	box(wtime,0,0);
	refresh();
	wrefresh(wnumb);
	wrefresh(wtime);
	signal(SIGINT,ctrlchandle);
	/*2.启动时间显示*/
	setitimer(ITIMER_REAL,&val,NULL);
	/*3.显示7位随机数*/
	int num;
	int i;
	while(1){
		num=0;
		for(i=0;i<7;i++){
			num=num*10+rand()%10;
		}
		mvwprintw(wnumb,1,1,"%07u",num);
		refresh();
		wrefresh(wnumb);
		wrefresh(wtime);
		usleep(10000);
	}
}
