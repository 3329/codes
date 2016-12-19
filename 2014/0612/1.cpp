#include <iostream>
#include <set>
using namespace std;

int main()
{
	int myints[] = {75,23,65,42,13,13};
	set<int> myset(myints, myints+6);
	for (set<int>::iterator itr = myset.begin();
			itr != myset.end(); itr++)
	{
		cout << *itr << " ";
	}
	cout << endl;

	myset.insert(20);
	myset.insert(30);
	myset.insert(10);
	while (!myset.empty())
	{
		cout << *myset.begin() << " ";
		myset.erase(myset.begin());
	}
	cout << endl;

	for (int i=100; i<110; i++)
	{
		myset.insert(i);
		cout << "Size: " << myset.size() << endl;
		cout << "Last: " << *myset.end() << endl;
	}
}
