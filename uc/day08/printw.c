#include <curses.h>

main()
{
	initscr();
	
	printw("���:%d,�߶�:%d",COLS,LINES);
	refresh();
	getch();
	endwin();
}
