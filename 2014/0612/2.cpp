#include <iostream>
#include <set>
#include <string>
using namspace std;

struct strLess
{
	bool operator()(const char* s1, const char* s2)
	{	
		return strcmp(s1, s2) < 0;
	}
};

void printSet(set<int> s)
{
	copy(s.begin(), s.end(), ostream_iterator<int>(cout, ","));
	cout << endl;
}

int main()
{
	set<int> s1;
	set<const char*, strLess> s2(strLess);
	set<int> s3(s1);
	int iArray[] = {13, 32, 19};
	set<int> s4(iArray, iArray+3);
	const char* szArray[] = {"hello", "dog", "bird"};
	set<const char*, strLess> s5(szArray, szArray+3, strLess());

	cout << "s1.insert(...): " << endl;
	for (int i=0; i<5; i++) s1.insert(i*10);
	printSet(s1);
}

