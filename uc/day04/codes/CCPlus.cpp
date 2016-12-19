#include <cstdlib>
#include <cstdio>
#include <new>
using namespace std;
int main()
{
	int *p1=(int*)malloc(4);
	int *p2=(int*)malloc(4);//new int(0);
	int *p3=(int*)malloc(4);
	int *p4=(int*)malloc(4);//new int(0);

	printf("%p\n",p1);
	printf("%p\n",p2);
	printf("%p\n",p3);
	printf("%p\n",p4);
	char s[200];

	int *p=new(s) int(0);

}

 
