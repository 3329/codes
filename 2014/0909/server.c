#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define VerifyErr(a, b) \
			if (a) { fprintf(stderr, "%s failed.\n", (b)); return 0; } \
			else fprintf(stderr, "%s success.\n", (b));

int CreateSock(int *pSock, int nPort, int nMax)
{
	struct sockaddr_in addrin;
	struct sockaddr *paddr = (struct sockaddr*)&addrin;

	int ret = 0; // save error message

	if (!((pSock != NULL) && (nPort > 0) && (nmax > 0)))
	{
		printf("input parameter error");
		ret = 1;
	}
	memset(&addrin, 0, sizeof(addrin));

	addrin.sin_family = AF_INET;
	addrin.sin_addr.s_addr = htonl(INADDR_ANY);
	addrin.sin_port = htos(nPort);

	if ((ret ==0) && (*pSock = socket(AF_INET, SOCK_STREAM, 0)) <=0)
	{
		printf("invoke socket error\n");
		ret = 1;
	}

	if ((ret == 0) && bind(*pSock, paddr, sizeof(addrin)) != 0)
	{
		printf("invoke bind error\n");
		ret = 1;
	}

	if ((ret == 0) && listen(*pSock, nMax) != 0)
	{
		printf("invoke listen error\n");
		ret = 1;
	}

	close (*pSock);
	return (ret);
}

int main()
{
	int nSock, nSock1;
	char buf[2048];

	// create sock
	nSock = nSock1 = 0;
	VerifyErr(CreateSock(&nSock, 9001, 9) != 0, "Create listen SOCKET");
	AcceptSock(&nSock1, nSock);
	memset(buf, 0, sizeof(buf));
	recv(nSock1, buf, sizeof(buf), 0);
	fprintf(stderr, buf);
	close(nSock);
	close(nSock1);

	return 0;
}

