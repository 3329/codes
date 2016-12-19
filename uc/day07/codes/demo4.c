#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
struct stu
{
	char name[20];
	short age;
	float score;
	char sex;
};
main()
{
	int fd;
	size_t len;//�ļ�����
	struct stu *p;//ӳ����ļ��ڴ��ַ
	struct stat st;
	struct stu *pend;
	int r;
	/*���ļ�*/
	fd=open("stu.dat",O_RDWR);
	if(fd==-1){//�ļ�������
		fd=open("stu.dat",O_RDWR|O_CREAT,0666);
		if(fd==-1){
			printf("�ļ��򿪻��ߴ���ʧ��:%m\n");
			exit(-1);
		}
	}
	/*ȡ���ļ���С*/
	r=fstat(fd,&st);
	if(r==-1){
		printf("��ȡ�ļ���Сʧ��:%m\n");
		close(fd);
		exit(-1);
	}
	len=st.st_size;
	/*�޸��ļ���СΪ�µĴ�С*/
	len+=3*sizeof(struct stu);
	r=ftruncate(fd,len);
	if(r==-1){
		printf("�޸��ļ���Сʧ��:%m\n");
		close(fd);
		exit(-1);
	}
	/*���ļ�ӳ��������ڴ��ַ*/
	p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);	
	if(p==NULL || p==(void*)-1){
		printf("ӳ��ʧ��:%m\n");
		close(fd);
		exit(-1);
	}
	/*��λ���ļ�ĩβ*/
	pend=p;
	pend+=(st.st_size/sizeof(struct stu));	 
	/*ͨ���ڴ��ַд��3����¼*/
	memset(pend,0,sizeof(struct stu));
	memcpy(pend->name,"tom",3);
	pend->age=18;
	pend->score=99.99f;
	pend->sex='m';
	
	pend++;
	memset(pend,0,sizeof(struct stu));
	memcpy(pend->name,"Jack",4);
	pend->age=19;
	pend->score=88.88f;
	pend->sex='m';
	
	pend++;
	memset(pend,0,sizeof(struct stu));
	memcpy(pend->name,"Rose",4);
	pend->age=20;
	pend->score=77.77f;
	pend->sex='f';	
	
	/*ж��ӳ��*/
	munmap(p,len);
	/*�ر��ļ�*/	
	close(fd);
}
