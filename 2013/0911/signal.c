#include <stdio.h>
#include <signal.h>

void f(int signum)
{
	printf("OUCH! \n");
}

main()
{
	int i;
	signal(SIGINT, SIG_DFL);

	for (i = 0; i<5; i++)
	{
		printf("Hello \n");
		sleep(1);
	}
}

