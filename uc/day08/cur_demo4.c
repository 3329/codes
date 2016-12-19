#include <curses.h>
#include <math.h>
main()
{
	WINDOW *wnum;
	int num=0;
	int i=0;
	/*初始化*/
	initscr();
	curs_set(0);
	/*产生显示随机数的子窗体*/
	wnum=derwin(stdscr,3,9,(LINES-3)/2,(COLS-9)/2);
	box(wnum,0,0);	
	while(1)
	{	
		num=0;
		/*产生随机数*/
		for(i=0;i<7;i++){
			num=num*10+rand()%10;
		}
		/*显示随机数*/
		mvwprintw(wnum,1,1,"%07d",num);
		refresh();
		wrefresh(wnum);
		/*暂停*/
		usleep(10000);//10毫秒
	}
	delwin(wnum);
	enwin();
}
