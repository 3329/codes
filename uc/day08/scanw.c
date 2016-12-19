#include <curses.h>
#include <stdlib.h>
#include <string.h>
main()
{
	char *ui="[        ]+[        ]=          ";
	char *info="是否继续计算(y/n):[ ]";
	int na,nb;
	
	/*初始化*/
	initscr();
	keypad(stdscr,TRUE);
	/*绘制界面*/
	mvaddstr(6,(COLS-strlen(ui))/2,ui);
	mvaddstr(LINES-3,(COLS-strlen(info))/2,info);
	refresh();
	/*循环输入*/
	while(1)
	{
		/*输入被加数*/
		mvscanw(6,(COLS-strlen(ui))/2+1,
						"%d",&na);
		/*输入加数*/
		mvscanw(6,(COLS-strlen(ui))/2+12,
						"%d",&nb);
		/*输出结果*/
		mvprintw(6,(COLS-strlen(ui))/2+22,
						 "%d",(na+nb));
		/*提示是否结束*/
		if(mvgetch(LINES-3,
			 (COLS-strlen(info))/2+strlen(info)-2
							)!='y'){
			break;
		}
	}	
	/*释放*/
	endwin();
}

