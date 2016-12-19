#include <string.h>

main()
{
	char *s = "kkkldkflksdlkflssssssssss";
	char *p = index(s, 'd');
	printf("%s\n", p);
	char *r = index(s, 's');
	printf("%s\n", r);

	char *p1 = memchr(s, 'd', 10);
	printf("%s\n", p1);

	char *ops = "01234567890123456789";
	char *oo = strstr(ops, "901");
	printf("%s\n", oo);
}
