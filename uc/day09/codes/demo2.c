#include <curses.h>
#include <math.h>
#include <sys/mman.h>
main()
{
	WINDOW *wnum;
	int *p;
	/*1.curses�빲������ĳ�ʼ��*/
	initscr();
	curs_set(0);
	noecho();
	wnum=derwin(stdscr,3,9,(LINES-3)/2,(COLS-9)/2);
	keypad(stdscr,TRUE);
	keypad(wnum,TRUE);
	refresh();
	wrefresh(wnum);
	
	p=mmap(0,4,PROT_READ|PROT_WRITE,
				MAP_ANONYMOUS|MAP_SHARED,0,0);
	*p=0;
	if(fork()){
		int num;
		int i;
		/*2.���������ʾ*/
		while(1){
			while(*p);/*��ѭ��������ʾ�Ƿ��ж�*/
			num=0;
			for(i=0;i<7;i++){
				num=num*10+rand()%10;
			}
			mvwprintw(wnum,1,1,"%07u",num);
			refresh();
			wrefresh(wnum);
			usleep(10000);			
		}
	}
	else{
		/*3.���̲���*/
		int ch;
		while(1){
			ch=getch();/*�ȴ�����*/
			if(ch=='\n'){/*�ж�����������*/
				if(*p==1){
					*p=0;
				}
				else{
					*p=1;
				}
			}
		}
	}		
}
