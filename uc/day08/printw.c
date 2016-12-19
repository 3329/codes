#include <curses.h>

main()
{
	initscr();
	
	printw("¿í¶È:%d,¸ß¶È:%d",COLS,LINES);
	refresh();
	getch();
	endwin();
}
