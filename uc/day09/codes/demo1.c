#include <curses.h>
#include <math.h>
#include <time.h>

main()
{
	WINDOW*wtime,*wnumb;	
	/*curses�ĳ�ʼ��*/
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
		/*7λ�������ʾ*/
		int num;
		int i=0;
		while(1)
		{
			/*��ͣ����7λ�����*/
			num=0;
			for(i=0;i<7;i++){
				num=num*10+rand()%10;
			}
			/*��ʾ�����*/
			mvwprintw(wnumb,1,1,"%07u",num);
			/*ˢ����Ļ*/
			refresh();
			wrefresh(wnumb);
			wrefresh(wtime);
			/*��ͣ*/
			usleep(10000);
		}
	}
	else{
		/*ʱ����ʾ*/
		time_t tt;
		struct tm *t;
		while(1){
			/*��ȡ��ǰʱ��*/
			tt=time(0);
			t=localtime(&tt);
			/*��ʾ��ǰʱ��*/
			mvwprintw(wtime,1,1,"%02u:%02u:%02u",
								t->tm_hour,t->tm_min,t->tm_sec);
			/*ˢ����Ļ*/
			refresh();
			wrefresh(wnumb);
			wrefresh(wtime);
			/*��ͣ*/
			sleep(1);
		}		
	}
	delwin(wnumb);
	delwin(wtime);
	endwin();
}
