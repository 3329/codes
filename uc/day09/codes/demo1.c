#include <curses.h>
#include <math.h>
#include <time.h>

main()
{
	WINDOW*wtime,*wnumb;	
	/*curses的初始化*/
	initscr();
	curs_set(0);
	wtime=derwin(stdscr,3,10,0,COLS-10);
	wnumb=derwin(stdscr,3, 9,(LINES-3)/2,(COLS-9)/2);
	box(wtime,0,0);
	box(wnumb,0,0);
	refresh();
	wrefresh(wtime);
	wrefresh(wnumb);
	
	if(fork())
	{
		/*7位随机数显示*/
		int num;
		int i=0;
		while(1)
		{
			/*不停产生7位随机数*/
			num=0;
			for(i=0;i<7;i++){
				num=num*10+rand()%10;
			}
			/*显示随机数*/
			mvwprintw(wnumb,1,1,"%07u",num);
			/*刷新屏幕*/
			refresh();
			wrefresh(wnumb);
			wrefresh(wtime);
			/*暂停*/
			usleep(10000);
		}
	}
	else{
		/*时间显示*/
		time_t tt;
		struct tm *t;
		while(1){
			/*获取当前时间*/
			tt=time(0);
			t=localtime(&tt);
			/*显示当前时间*/
			mvwprintw(wtime,1,1,"%02u:%02u:%02u",
								t->tm_hour,t->tm_min,t->tm_sec);
			/*刷新屏幕*/
			refresh();
			wrefresh(wnumb);
			wrefresh(wtime);
			/*暂停*/
			sleep(1);
		}		
	}
	delwin(wnumb);
	delwin(wtime);
	endwin();
}
