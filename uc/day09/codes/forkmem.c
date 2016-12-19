#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
main()
{	
	int fd;
	fd=open("a.txt",O_RDWR|O_CREAT,0666);
	if(fork())
	{
		write(fd,"Hello",5);
		sleep(5);
	}
	else
	{		
		sleep(1);
		char str[6]={0};
		lseek(fd,0,SEEK_SET);
		read(fd,str,5);
		printf("%s\n",str);
	}
}
