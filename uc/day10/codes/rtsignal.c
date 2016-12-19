#include <unistd.h>
#include <signal.h>
#include <stdio.h>
/*
void handle(int s)
{
	printf("–≈∫≈¥¶¿Ì!\n");
}*/
main()
{
	signal(2,SIG_IGN);
	printf("%d\n",getpid());
	while(1);
}
