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
		printf("�������ݿ�ʧ��!\n");
		exit(-1);
	}
	printf("�������ѯ���û�����\n");
	memset(name,0,sizeof(name));
	r=scanf("%s",name);	
	printf("��Ҫ��ѯ��������%s\n",name);
	float salary=db.querySalaryByName(name);
	printf("%s��нˮ��:%.2f\n",name,salary);
	db.closedb();
}
