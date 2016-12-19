#include <stdio.h>
#include <fcntl.h>


int main()
{
	int fd = open("./msg.c", O_RDWR|O_CREAT|0666);
}
