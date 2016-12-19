#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void print()
{
	for (int i=0; i<5; i++)
	{
		printf("Hello world!\n");
		sleep(1);
	}
}

main()
{
	print();
	close(STDOUT_FILENO);
	print();
	open(STDOUT_FILENO);
	print();
	return 0;
}

fd=open("/dev/stdout",O_WRONLY); 
if (fd < 0) {
	fprintf(stderr, "errno %d\n", errno);
	return 0;
}
close(STDOUT_FILENO);
dup(fd);
printf("hello!\n");


