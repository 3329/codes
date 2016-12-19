#include <stdio.h>
#include <unistd.h>
#include <signal.h>

main()
{
	int i=0;
	for(i=0;i<10;i++){
		kill(3759,2);
	}
}
