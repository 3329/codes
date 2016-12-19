#include <signal.h>
#include <stdio.h>
#include <unistd.h>
void handle(int s)
{
	printf(" ’µΩ–≈∫≈!\n");
} 
main()
{
	signal(2,handle);
	printf("pid=%d\n",getpid());
	while(1);
}
