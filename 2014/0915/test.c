#include <stdio.h>
#include <time.h>


int str2epoch(const char* data_str)
{
	char fmt[] = "%Y-%m-%d-%H:%M:%S";
	struct tm t;
	time_t tt = mktime(&t);
	if (strptime(data_str, fmt, &t))
	{
		printf("%d\n", (int)tt);
		return (int)tt;
	}
	return -1;
}

void epoch2str(const int epoch_time)
{
	time_t tt = epoch_time;
	struct tm *t = localtime(&tt);
	char ss[50];
	sprintf(ss, "%d-%02u-%02u %02u:%02u:%02u", 
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec);
	printf("%s\n", ss);
}

main()
{
	char* data_str = "2014-09-16 09:59:51";
	int dd = str2epoch(data_str);
	epoch2str(dd);
	
}
