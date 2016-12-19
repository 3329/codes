#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>

extern int errno;

int main()
{	
	FILE *fp;
	char buf[255];
	assert((mkfifo("myfifo", S_IFIFO|0666) > 0) || (errno == EEXIST));

	while (1)
	{
		assert((fp = open("myfifo", "w")) != 0);
		printf("please input: ");
		fgets(buf, sizeof(buf), stdin);
		fputs(buf, fp);
		fclose(fp);
		if (strncmp(buf, "quit", 4) == 0 || strncmp(buf, "exit", 4) == 0)
		{
			break;
		}
	}

	return 0;

}
