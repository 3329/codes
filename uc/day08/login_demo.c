#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
/*��ʼ��*/
void Init();
void DrawLoginUI();
void Destroy();
main()
{
	Init();
	DrawLoginUI();
	Destroy();
}
void DrawLoginUI()
{
	char *header="���żƷѹ���ϵͳ";
	char *user="�û�:_________";
	char *pass="����:_________";
	attron(A_BOLD|COLOR_PAIR(1));
	mvaddstr(2,(COLS-strlen(header))/2,header);
	attroff(A_BOLD);
	mvhline(3,(COLS-strlen(header))/2,'=',strlen(header));
	attron(A_BOLD);
	mvaddstr(6,(COLS-strlen(user))/2,user);
	mvaddstr(8,(COLS-strlen(pass))/2,pass);
	
	attroff(A_BOLD|COLOR_PAIR(1));
}
void Init()
{
	setlocale(LC_ALL,"C");
	initscr();
	start_color();
	init_pair(1,COLOR_YELLOW,COLOR_BLUE);
	bkgd(COLOR_PAIR(1));	
}

void Destroy()
{
	getch();
	endwin();
}
