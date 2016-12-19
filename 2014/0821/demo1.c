#include <curses.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

pthread_t thtime, thnumb;
WINDOw *wtime, *wnumb;

int isstop = 0;
pthread_mutex_t m;

void *timerun(void *data)
{
	time_t tt;
	struct tm *t;
	while (1)
	{
		pthread_mutex_lock(&m);
		tt = time(0);
		t = localtime(&tt);
		mvwprintw(wtime, 1, 1, "%02u:%02u:%02u",
				t->tm_hour, t->tm_min, t->tm_sec);

		refresh();
		wrefresh(wtime);
		wrefresh(wnumb);
		pthread_mutex_unlock(&m);
		sleep(1);
	}
}


void refreshWindown()
{
	refresh();
	wrefresh(wtime);
	wrefresh(wnumb);
}

/* print random num */
void *numbrun(void *data)
{
	int num, i;
	while (1)
	{
		while (isstop);
		pthread_mutex_lock(&m);
		num = 0;
		for (i=0; i<7; i++)
		{
			num = num * 10  + rand()%10;
		}
		mvwprintw(wnumb, 1, 1, "%07u", num);
		refresh();
		wrefresh(wtime);
		wrefresh(wnumb);
		pthread_mutex_unlock(&m);
		usleep(10000);
	}
}


main()
{
	initscr();
	curs_set(0);
	noecho();
	wtime = derwin(stdscr, 3, 11, 0, COLS-11);
	wnumb = derwin(stdscr, 3, 9, (LINES-3)/2, (COLS-9)/2);
	keypad(wtime, TRUE);
	keypad(wnumb, TRUE);
	keypad(stdscr, TRUE);
	box(wtime, 0, 0);
	box(wnumb, 0, 0);
	refreshWindon();
	
	pthread_mutex_init(&m, 0);
	pthread_create(&thtime, 0, timerun, 0);
	pthread_create(&thnumb, 0, numbrun, 0);

	int ch;
	while (1)
	{
		ch = getch();
		if (ch == '\n')
		{
			isstop = (!isstop);
		}
		pthread_join(thtime, (void**)0);
		pthread_join(thnumb, (void**)0);
		delwin(wtime);
		delwin(wnumb);
		endwin();
	}

}

