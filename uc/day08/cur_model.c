#include <curses.h>
#include <unistd.h>
main()
{
	/*��ʼ��curses*/
	initscr();
	curs_set(1);
	/*���*/
	/*border('1','2','3','4','5','6','7','8');*/
	//wborder(stdscr,0,0,0,0,0,0,0,0);
	//box(stdscr,'a','b');
	box(stdscr,0,0);
	
	//move(2,2);
	//hline('-',20);
	mvhline(2,2,'-',20);
	
	mvaddstr(5,20,"Hello �ն�IO��");
	/*ˢƽ��*/
	refresh();
	/*��ͣ:ֱ������һ���ַ�*/
	getch();
	/*�ͷ�*/
	endwin();
}

