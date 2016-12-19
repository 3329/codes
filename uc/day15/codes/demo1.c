#include <curses.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
pthread_t thtime,thnumb;
WINDOW *wtime,*wnumb;
int isstop=0;
pthread_mutex_t m;

/*显示时间*/
void *timerun(void* data){
	time_t tt;
	struct tm *t;
	while(1){
		/*得到时间*/
		pthread_mutex_lock(&m);
		tt=time(0);
		t=localtime(&tt);
		/*显示时间*/
		mvwprintw(wtime,1,1,"%02u:%02u:%02u",
						 t->tm_hour,t->tm_min,t->tm_sec);
		/*刷屏*/
		refresh();
		wrefresh(wtime);
		wrefresh(wnumb);
		pthread_mutex_unlock(&m);
		/*暂停1秒*/
		sleep(1);
	}
}
/*显示随机数*/
void *numbrun(void *data){
	int num;
	int i;
	while(1){
		while(isstop);		
		pthread_mutex_lock(&m);
		num=0;
		for(i=0;i<7;i++){
			num=num*10+rand()%10;
		}
		mvwprintw(wnumb,1,1,"%07u",num);
		refresh();
		wrefresh(wtime);
		wrefresh(wnumb);
		pthread_mutex_unlock(&m);
		usleep(10000);
	}
}

main()
{
	initscr();
	curs_set(0);
	noecho();	
	wtime=derwin(stdscr,3,11,0,COLS-11);
	wnumb=derwin(stdscr,3,9,(LINES-3)/2,(COLS-9)/2);
	keypad(wtime,TRUE);
	keypad(wnumb,TRUE);
	keypad(stdscr,TRUE);	
	box(wtime,0,0);
	box(wnumb,0,0);
	refresh();
	wrefresh(wtime);
	wrefresh(wnumb);
	pthread_mutex_init(&m,0);	
	pthread_create(&thtime,0,timerun,0);
	pthread_create(&thnumb,0,numbrun,0);
	/*键盘输入*/
	int ch;
	while(1){
		ch=getch();
		if(ch=='\n'){
			isstop++;
			isstop%=2;
		}
	}	
	pthread_join(thtime,(void**)0);
	pthread_join(thnumb,(void**)0);
	pthread_mutex_destroy(&m);	
	delwin(wtime);
	delwin(wnumb);
	endwin();
}

