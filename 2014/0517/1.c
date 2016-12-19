#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s = "12345678";
	char *s1 = s.data();
	cout << s1+3 << endl;
}

