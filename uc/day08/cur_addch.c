#include <curses.h>

main()
{
	initscr();
	start_color();/*启动颜色支持*/
	init_pair(1,COLOR_RED,COLOR_GREEN);
	init_pair(2,COLOR_CYAN,COLOR_BLUE);
	mvaddch(10,30,'A'|COLOR_PAIR(1));
	
	attron(A_UNDERLINE|COLOR_PAIR(2));
	mvaddch(2,2,'A');
	attroff(COLOR_PAIR(2));
	mvaddch(2,3,'B');
	attroff(A_UNDERLINE);
	mvaddch(2,4,'C');
	mvaddch(2,5,'D');
	refresh();	
	getch();
	endwin();
}
