#include <unistd.h>
#include <stdio.h>

int main()
{
	char buf[256];
	ssize_t r;
	r=read(0,buf,255);/*��һ���ֽڷ�\0�ַ�*/
	if(r==0) printf("������������!\n");
	if(r>0) {
		buf[r]=0;//Ϊ�ַ�����һ�����ַ�
		printf("%s\n",buf);
	}
	if(r==-1){
		printf("��ȡ����!\n");
	}
	return 0;
}

