#include <stdio.h>
int main(int args,char**argv,char**arge)
{
	while(arge&&*arge){
		printf("%s\n",*arge);
		arge++;
	}
}
