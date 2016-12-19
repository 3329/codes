#include <stdio.h>
#include <unistd.h>


static int fd1[2], fd2[2];

void TELL_WAIT()
{
	if (pipe(fd1) < 0 || pipe(fd2) < 0)
	{
		printf("pipe() error");
	}
}

void TELL_PARENT(pid_t pid)
{
	if (write(fd2[1], "c", 1) != 1)
	{
		printf("write error\n");
	}
}


int main()
{
	
}


