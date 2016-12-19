#include <stdio.h>
#include <string.h>

int main ()
{
	char str[] = "This is a sample string./xml./.xml.tar.gz";
	char * pch;
	pch=strrchr(str,'.');

	printf ("%s\n", pch);
	return 0;
}

