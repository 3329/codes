#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

#ifndef DDD_LogServer_H
#define DDD_LogServer_H

namespase DDD{
class DDD_LogServer
{
private:
	map<int, string>		mLogidMap;	// map<logid, log_path>

public:
	DDD_LogServer();
	~DDD_LogServer();

	int 	addLog(const string &data);
	bool	deleteLog(const int logid);
	bool	modifyLog(const string &data);
	string 	getLog(const int logid);
};
};
#endif
