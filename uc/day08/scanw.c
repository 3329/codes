#include <curses.h>
#include <stdlib.h>
#include <string.h>
main()
{
	char *ui="[        ]+[        ]=          ";
	char *info="�Ƿ��������(y/n):[ ]";
	int na,nb;
	
	/*��ʼ��*/
	initscr();
	keypad(stdscr,TRUE);
	/*���ƽ���*/
	mvaddstr(6,(COLS-strlen(ui))/2,ui);
	mvaddstr(LINES-3,(COLS-strlen(info))/2,info);
	refresh();
	/*ѭ������*/
	while(1)
	{
		/*���뱻����*/
		mvscanw(6,(COLS-strlen(ui))/2+1,
						"%d",&na);
		/*�������*/
		mvscanw(6,(COLS-strlen(ui))/2+12,
						"%d",&nb);
		/*������*/
		mvprintw(6,(COLS-strlen(ui))/2+22,
						 "%d",(na+nb));
		/*��ʾ�Ƿ����*/
		if(mvgetch(LINES-3,
			 (COLS-strlen(info))/2+strlen(info)-2
							)!='y'){
			break;
		}
	}	
	/*�ͷ�*/
	endwin();
}

