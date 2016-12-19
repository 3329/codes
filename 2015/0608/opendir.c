#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void sigfpe_func()
{	
	printf("datata\n");
	exit();
}


int 
main(int argc, char *argv[])
{
	signal(SIGFPE, sigfpe_func);
	int a = 10 / 0;

	printf("uid:%d, gid:%d\n", getuid(), getgid());
	fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
	fprintf(stderr, "E2BIG: %s\n", strerror(E2BIG));
	errno = ENOPKG;
	perror(argv[0]);
	printf("current pid : %d\n", getpid());
	printf("current ppid : %d\n", getppid());
	exit(0);


	DIR 			*dp; 
	struct dirent 	*dirp;

	if (argc != 2) 
	{
		printf("useage: ls directory_name\n");
		exit(0);
	}
	
	if (dp = opendir(argv[1]))
	{
		while ((dirp = readdir(dp)) != NULL)
			printf("%s\n", dirp->d_name);
		closedir(dp);
	}
	else
	{
		printf("cannot open %s\n", argv[1]);
	}	

	exit(0);
}

