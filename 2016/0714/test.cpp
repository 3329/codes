#include <iostream>
#include <linux/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

typedef uint32_t                u32;
typedef uint64_t                u64;


 bool AosConvertAsciiBinary(string &str)
 {
     // This function checks whether 'str' is in the format:
     //      0xdd
     // where dd are two hex codes. If yes, it converts str
     // to one character whose ASCII code is 0xdd.
     if (str.length() < 4 && str.length() % 2 != 0) return true;

     char *data = (char *)str.data();
     if (!data) return true;
     if (data[0] != '0' || (data[1] != 'x' && data[1] != 'X')) return true;

     char c = data[2];
     u32 code1 = 0;
     if ((c >= '0' && c <= '9'))
     {
         code1 = c - '0';
     }
     else
     {
         if (c >= 'a' && c <= 'f') code1 = c - 'a' + 10;
         else return true;
     }
	 cout << code1 << endl;

     c = data[3];
     u32 code2 = 0;
     if ((c >= '0' && c <= '9'))
     {
         code2 = c - '0';
     }
     else
     {
         if (c >= 'a' && c <= 'f') code2 = c - 'a' + 10;
         else return true;
     }

	 cout << code2 << endl;
     str.resize(1);
     data[0] = (char)((code1 << 4) + code2);
     return true;
 }

string readContentsFromFile(const string &fname)
{
	FILE* f = fopen(fname.data(), "rb");
	int n;
	char buf[4096];
	bzero(buf, sizeof(buf));
	while ((n = fread(buf, 1, 4096, f)) > 0)
	{
		cout << "read bytes:" << n << endl;
		cout << buf << endl;
	}
	fclose(f);
}


int main()
{
	string fname = "/home/young/expr.log";
	readContentsFromFile(fname);
	return true;
}
