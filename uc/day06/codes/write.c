#include <unistd.h>
#include <stdio.h>
int main()
{
	char s[]="Hello!";
	int a=97;
	float f=88.99f;
	char  c='M';
	write(2,s,6);
	write(2,&a,sizeof(int));
	write(2,&f,sizeof f);
	write(2,&c,sizeof(char));
	
	return 0;
}
