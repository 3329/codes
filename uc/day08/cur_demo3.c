#include <curses.h>
#include <stdlib.h>
#include <string.h>
char  *header="���żƷѹ���ϵͳ";
char  *user="�û�[        ]";
char  *pass="����[        ]";
int x,y;/*��¼����λ��*/
char szuser[9];/*������û��������*/
char szpass[9];
void init();
void destroy();
void drawlogin();
void inputlogin();
void drawwelcome();
main()
{
	/*��ʼ��curses*/
	init();
	/*���Ƶ�¼����*/
	drawlogin();
	/*�����û������*/
	inputlogin();
	/*��ʾ��ӭ����*/
	drawwelcome();
	/*�ͷ�curses*/
	destroy();
}
void drawwelcome(){
	int ch;
	curs_set(0);
	clear();
	mvaddstr(LINES/2,(COLS-6)/2,"��¼OK");
	noecho();
	while(1){
		ch=getch();
		if(ch=='y' || ch=='Y'){
			break;
		}
	}
}
void inputlogin(){
	while(1){
		/*��ʼ���ڴ�*/	
		memset(szuser,0,sizeof(szuser));
		memset(szpass,0,sizeof(szpass));
		/*�����������*/
		y=8;
		x=(COLS-strlen(user))/2+strlen("�û�[");
		mvaddstr(y,x,"        ");
		y=10;
		x=(COLS-strlen(pass))/2+strlen("����[");
		mvaddstr(y,x,"        ");
		/*�����û���*/
		y=8;
		x=(COLS-strlen(user))/2+strlen("�û�[");
		mvgetnstr(y,x,szuser,8);
		/*�������*/
		noecho();
		y=10;
		x=(COLS-strlen(pass))/2+strlen("����[");
		mvgetnstr(y,x,szpass,8);
		echo();
		if(strcmp(szuser,"tom")==0 && 
			 strcmp(szpass,"123")==0){
			break;
		}
	}
}
void drawlogin(){	
	mvaddstr(3,(COLS-strlen(header))/2,header);
	mvaddstr(8,(COLS-strlen(user))/2,user);
	mvaddstr(10,(COLS-strlen(pass))/2,pass);
	refresh();
}
void init(){
	initscr();
	keypad(stdscr,TRUE);
}
void destroy()
{
	endwin();
}
