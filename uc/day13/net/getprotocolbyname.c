#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
/*
#include <netdb.h>
struct protoent *getprotoent(void);
struct protoent *getprotobyname(const char *name);
struct protoent *getprotobynumber(int proto);
void setprotoent(int stayopen);
void endprotoent(void);
	struct protoent {
		char    *p_name;        // official protocol name
      char    **p_aliases;    // alias list 
      int     p_proto;        // protocol number 
}
*/
main()
{
	struct protoent *prot=getprotobyname("icmp");
	if(prot!=NULL)
	{
		printf("%d\n",prot->p_proto);
	}
	printf("%d\n",IPPROTO_ICMP);
}
