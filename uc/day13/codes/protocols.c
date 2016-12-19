#include <stdio.h>
#include <netdb.h>
main()
{
	char *proto="udp";/*字符串不区分大小写*/
	struct protoent *ent;
	ent=getprotobyname(proto);
	if(ent){
		printf("%s:%d\n",proto,ent->p_proto);
	}
}
