#include<stdio.h>
#include<stdarg.h>
FILE *fp;
int vfpf(char *fmt, ...)
{
	printf("%s\n", fmt);
	printf("--------------------\n");
	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vfprintf(fp, fmt, argptr);
	va_end(argptr);
	return(cnt);
}
int main(void)
{
	int inumber = 30;
	float fnumber = 90.0;
	char string[4] = "abc";
	fp = tmpfile();
	if (fp == NULL)
	{
		perror("tmpfile() call");
		exit(1);
	}
	vfpf("%d %f %s", inumber, fnumber, string);
	rewind(fp);
	fscanf(fp,"%d %f %s", &inumber, &fnumber, string);
	printf("%d %f %s\n", inumber, fnumber, string);
	fclose(fp);
	return 0;
}
