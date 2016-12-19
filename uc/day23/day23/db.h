#ifndef TARENA_DB_H
#define TARENA_DB_H
class Db{
public:
	int opendb(char *account);
	int closedb();
	float querySalaryByName(char *name);	
};
#endif
