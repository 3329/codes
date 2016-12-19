#include <stdio.h>
#define PAGELEN 24
#define LINELEN 512

void doMore(FILE *);
int seeMore();

int main(int argc, char **agrv)
{
	FILE *fp;
	if (ac == 1)
	{
		doMore(stdin);
	}
	else 
	{
		while (--argc)
		{
			if ((fp = fopen(* ++av, "r")) != NULL)
			{

			}
		}
	}

}

