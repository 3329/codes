#include <stdio.h>
#include <netdb.h>
main()
{
	char *proto="udp";/*�ַ��������ִ�Сд*/
	struct protoent *ent;
	ent=getprotobyname(proto);
	if(ent){
		printf("%s:%d\n",proto,ent->p_proto);
	}
}
