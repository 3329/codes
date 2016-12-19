#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ofstream test("./log.txt");
	streambuf* oldbuf = cout.rdbuf(test.rdbuf());

	cout << "Hello world!" << endl;
	cout << "Hello world!" << endl;
	cout << "Hello world!" << endl;
	cout << "Hello world!" << endl;
	cout << "Hello world!" << endl;
	cout << "Hello world!" << endl;
	cout << "Hello world!" << endl;

	cout.rdbuf(oldbuf);
	cout << "PPPPPPPPPPPPPPPP" << endl;
	cout << "PPPPPPPPPPPPPPPP" << endl;
	cout << "PPPPPPPPPPPPPPPP" << endl;
	cout << "PPPPPPPPPPPPPPPP" << endl;

	streambuf* oldbuf2 = cout.rdbuf(test.rdbuf());
	cout <<  "2222222222222222222222" << endl;
	cout <<  "2222222222222222222222" << endl;
	cout <<  "2222222222222222222222" << endl;
	cout <<  "2222222222222222222222" << endl;

	cout.rdbuf(oldbuf2);
	cout << "PPPPPPPPPPPPPPPP" << endl;
	cout << "PPPPPPPPPPPPPPPP" << endl;
	cout << "PPPPPPPPPPPPPPPP" << endl;
	cout << "PPPPPPPPPPPPPPPP" << endl;
	cout <<  "2222222222222222222222" << endl;
	cout <<  "2222222222222222222222" << endl;

	oldbuf2 = cout.rdbuf(test.rdbuf());
	oldbuf2 = cout.rdbuf(test.rdbuf());
	cout << "3333333333333333333333333333" << endl;
	cout << "3333333333333333333333333333" << endl;
	cout << "3333333333333333333333333333" << endl;
	cout << "3333333333333333333333333333" << endl;
	cout.rdbuf(oldbuf2);
	cout << "44444444444444444444444" << endl;
	cout << "44444444444444444444444" << endl;
	cout << "44444444444444444444444" << endl;
	cout << "44444444444444444444444" << endl;
	cout << "44444444444444444444444" << endl;
}

