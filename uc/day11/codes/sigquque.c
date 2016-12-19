#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

main()
{
	union sigval  val;
	val.sival_int=9999;
	sigqueue(3949,SIGINT,val);	
}
