#include <curses.h>
#include <math.h>
main()
{
	WINDOW *wnum;
	int num=0;
	int i=0;
	/*��ʼ��*/
	initscr();
	curs_set(0);
	/*������ʾ��������Ӵ���*/
	wnum=derwin(stdscr,3,9,(LINES-3)/2,(COLS-9)/2);
	box(wnum,0,0);	
	while(1)
	{	
		num=0;
		/*���������*/
		for(i=0;i<7;i++){
			num=num*10+rand()%10;
		}
		/*��ʾ�����*/
		mvwprintw(wnum,1,1,"%07d",num);
		refresh();
		wrefresh(wnum);
		/*��ͣ*/
		usleep(10000);//10����
	}
	delwin(wnum);
	enwin();
}
