#include <unistd.h>
#include <stdio.h>
/*�����ⲿȫ�ֱ���*/
extern  char **environ;
main()
{
	/*environΪ�գ�����ָ����ַ���Ϊ��,�ͽ���*/
	while(environ && *environ)
	{
		printf("%s\n",*environ);
		environ++;/*ָ����һ���ַ���*/
	}
}
