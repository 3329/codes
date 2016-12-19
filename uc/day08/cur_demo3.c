#include <curses.h>
#include <stdlib.h>
#include <string.h>
char  *header="电信计费管理系统";
char  *user="用户[        ]";
char  *pass="口令[        ]";
int x,y;/*记录输入位置*/
char szuser[9];/*输入的用户名与口令*/
char szpass[9];
void init();
void destroy();
void drawlogin();
void inputlogin();
void drawwelcome();
main()
{
	/*初始化curses*/
	init();
	/*绘制登录界面*/
	drawlogin();
	/*输入用户与口令*/
	inputlogin();
	/*显示欢迎界面*/
	drawwelcome();
	/*释放curses*/
	destroy();
}
void drawwelcome(){
	int ch;
	curs_set(0);
	clear();
	mvaddstr(LINES/2,(COLS-6)/2,"登录OK");
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
		/*初始化内存*/	
		memset(szuser,0,sizeof(szuser));
		memset(szpass,0,sizeof(szpass));
		/*清空输入区域*/
		y=8;
		x=(COLS-strlen(user))/2+strlen("用户[");
		mvaddstr(y,x,"        ");
		y=10;
		x=(COLS-strlen(pass))/2+strlen("口令[");
		mvaddstr(y,x,"        ");
		/*输入用户名*/
		y=8;
		x=(COLS-strlen(user))/2+strlen("用户[");
		mvgetnstr(y,x,szuser,8);
		/*输入口令*/
		noecho();
		y=10;
		x=(COLS-strlen(pass))/2+strlen("口令[");
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
