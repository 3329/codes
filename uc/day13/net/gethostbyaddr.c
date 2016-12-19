/*
gethostbyaddr

#include <sys/socket.h>	//for AF_INET
   struct hostent *gethostbyaddr(const void *addr, int len, int type);

   struct hostent {
   	char    *h_name;        // official name of host
      char    **h_aliases;    // alias list 
      int     h_addrtype;     // host address type 
      int     h_length;       // length of address 
      char    **h_addr_list;  // list of addresses 
         }
	#define h_addr  h_addr_list[0]  //for backward compatibility
*/
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

main()
{
	char ip[]={192,168,1,158};/*使用的是network order*/
	struct hostent *hptr;
	hptr=gethostbyaddr(ip,4,AF_INET);
	printf("host name:%s\n",hptr->h_name);
}
