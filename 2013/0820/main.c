#include <unistd.h>

int main()
{
	execl("/bin/bash", "bash", "-c", "find / -type f", (char *)0);
	sleep(10);
}

