#include <curses.h>
main()
{
	int x,y;
	int ch;
	initscr();/*初始化curses*/
	x=COLS/2;
	y=LINES/2;
	keypad(stdscr,TRUE);/*启动功能键处理*/
	noecho();/*禁止回显*/
	curs_set(0);
	while(1){
		//clear();
		mvaddch(y,x,'A');
		refresh();
		ch=getch();
		switch(ch)
		{
			case KEY_RIGHT:
				x++;
				break;
			case KEY_DOWN:
				y++;
				break;
			case KEY_LEFT:
				x--;
				break;
			case KEY_UP:
				y--;
				break;	
		}		
	}
	
	endwin();
}
