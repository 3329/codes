#include <curses.h>
#include <time.h>
main()
{
	time_t tt;
	struct tm *t;
	initscr();
	while(1){
		/*��ȡʱ��*/
		tt=time(NULL);
		t=localtime(&tt);
		/*���ʱ��*/
		mvprintw(LINES/2,(COLS-8)/2,"%02d:%02d:%02d",
						t->tm_hour,t->tm_min,t->tm_sec);
		refresh();
		sleep(1);
	}	
	endwin();
}
