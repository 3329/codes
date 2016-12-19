#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	char buf[BUFSIZ];
	printf("%d\n", sizeof(buf));
	printf("%ld\n", BUFSIZ);
	if (argc != 2)
	{
		fprintf(stderr, "useage: write0 ttyname\n");
		exit(1);
	}

	// open devices
	fd = open(argv[1], O_WDONLY);
	if (fd == -1)
	{
		perror(argv[1]);
		exit(1);
	}

	// loop untill EOF on input
	while (fgets(buf, BUFSIZ, stdin) != NULL)
	{
		if (write(fd, buf, strlen(buf)) == -1)
			break;
	}
	close(fd);
}
