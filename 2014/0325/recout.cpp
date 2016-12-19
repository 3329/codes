#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ofstream logfile("log.txt");
	streambuf *oldbuf = cout.rdbuf(logfile.rdbuf());

	for (int i=0; i<20; i++) cout << "Hello world!" << endl;

	// recovery
	cout.rdbuf(oldbuf);
	cout << "morning..." << endl;
}

