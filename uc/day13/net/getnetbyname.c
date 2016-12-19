/*
	#include <netdb.h>
   struct netent *getnetent(void);
	struct netent *getnetbyname(const char *name);
	struct netent *getnetbyaddr(long net, int type);
	void setnetent(int stayopen);
	void endnetent(void);

	struct netent {
		char    *n_name;          // official network name
      char    **n_aliases;      // alias list 
      int     n_addrtype;       // net address type 
      unsigned long int n_net;  // network number 
	}

相关文件： /etc/networks

*/
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

main()
{
	setnetent(1);
	struct netent *net;
	while((net=getnetent())!=NULL)
	{
		printf("%s,%d,%u\n",net->n_name,net->n_addrtype,net->n_net);
	}
	endservent();
}
