#include <curses.h>
#include <unistd.h>
main()
{
	/*初始化curses*/
	initscr();
	curs_set(1);
	/*输出*/
	/*border('1','2','3','4','5','6','7','8');*/
	//wborder(stdscr,0,0,0,0,0,0,0,0);
	//box(stdscr,'a','b');
	box(stdscr,0,0);
	
	//move(2,2);
	//hline('-',20);
	mvhline(2,2,'-',20);
	
	mvaddstr(5,20,"Hello 终端IO！");
	/*刷平屏*/
	refresh();
	/*暂停:直到输入一个字符*/
	getch();
	/*释放*/
	endwin();
}

