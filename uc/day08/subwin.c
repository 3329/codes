#include <curses.h>
WINDOW *wmain;
WINDOW *wsub;
WINDOW *wsubsub;

main()
{
	/*������*/
	wmain=initscr();/*wmain==stdscr*/
	/*��һ���Ӵ���*/
	wsub=derwin(wmain,10,40,2,2);
	/*�ڶ����Ӵ���*/
	wsubsub=derwin(wsub,5,20,3,3);
	box(wmain,0,0);
	box(wsub,0,0);
	box(wsubsub,0,0);
	refresh();
	wrefresh(wsub);
	wrefresh(wsubsub);
	
	getch();
	delwin(wsubsub);
	delwin(wsub);
	endwin();
}

