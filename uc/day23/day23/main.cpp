#include "db.h"
#include <cstdio> 
#include <cstdlib>
#include <cstring>
int main()
{
	Db db;
	int r;
	char name[30];
	r=db.opendb("openlab/open123");
	if(r<0){
		printf("连接数据库失败!\n");
		exit(-1);
	}
	printf("清输入查询的用户名：\n");
	memset(name,0,sizeof(name));
	r=scanf("%s",name);	
	printf("你要查询的姓名：%s\n",name);
	float salary=db.querySalaryByName(name);
	printf("%s的薪水是:%.2f\n",name,salary);
	db.closedb();
}
