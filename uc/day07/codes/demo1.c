#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
	int fd;//�ļ���������
	int r;//��ȡ����ֵ
	char name[32];//����û�
	short len;//���IP����
	char ip[257];//���IP
	int line=0;//��ȡ��¼����
	/*1.���ļ�*/
	fd=open("wtmpx",O_RDONLY);
	if(fd==-1) printf("open:%m\n"),exit(-1);
	/*2.ѭ����ȡ*/
	while(1){
		/*3.��λÿ�м�¼�Ŀ�ʼλ��*/
		lseek(fd,line*372,SEEK_SET);
		/*4.��ȡ�û���*/
		r=read(fd,name,32);
		/*5.�ж���¼�Ƿ����*/
		if(r<=0) break;
		/*name[r]=0;*/
		/*5.��λ*/
		lseek(fd,80,SEEK_CUR);
		/*6.��ȡIP����*/
		read(fd,&len,sizeof(len));
		/*7.���ֽ���ת��*/
		len=(len & 255)<<8 | (len >> 8 & 255);
		/*8.��λ*/
		/*����Ҫ��λ*/
		/*9.��ȡIP��ַ*/
		read(fd,ip,sizeof(ip));
		/*10.��IP��ַ������ֹ�ַ�*/
		ip[len]='\0';
		/*11.���*/
		printf("%s,%s\n",name,ip);
		line++;
	}
	//12.�ر��ļ�
	close(fd);				 
	return 0;
}
