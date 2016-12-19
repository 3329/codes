#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
void printOn()
{
	freopen("/dev/tty", "w", stdout);
}
void printOff()
{
	fclose(stdout);
}
int main(void)
{
	char buf[80];
	getcwd(buf, sizeof(buf));
printf("cwd: %s\n", buf);
	char *name = "/1.txt";
	strcat(buf, name);
printf("cwd: %s\n", buf);

int fdstdout = dup(STDOUT_FILENO);
printf("fdstdout: %d\n", fdstdout);


int fd = open(buf, O_RDWR|O_TRUNC|O_CREAT, S_IREAD|S_IWRITE|S_IROTH);
int fd2 = dup2(fd, STDOUT_FILENO);

	while(1)
	{
	
		sleep(1);
		printf("aaaaaaaaaaa\n");
		printf("bbbbbbbbbbb\n");
		close(fd2);
		fdopen(fdstdout, "w+");
	}

	return 0;
}
