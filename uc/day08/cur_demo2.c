#include <curses.h>
main()
{
	int x,y;
	int ch;
	initscr();/*��ʼ��curses*/
	x=COLS/2;
	y=LINES/2;
	keypad(stdscr,TRUE);/*�������ܼ�����*/
	noecho();/*��ֹ����*/
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
