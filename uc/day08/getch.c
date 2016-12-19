#include <curses.h>
main()
{
	int ch;
	initscr();
	keypad(stdscr,TRUE);
	while(1){
		ch=mvgetch(1,1);
		mvprintw(5,1,"     ");
		mvprintw(5,1,"%d:%c",ch,ch);
		refresh();
	}	
	endwin();
}
