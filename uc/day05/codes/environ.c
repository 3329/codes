#include <unistd.h>
#include <stdio.h>
/*声明外部全局变量*/
extern  char **environ;
main()
{
	/*environ为空，或者指向的字符串为空,就结束*/
	while(environ && *environ)
	{
		printf("%s\n",*environ);
		environ++;/*指向下一个字符串*/
	}
}
