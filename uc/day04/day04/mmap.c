#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
main()
{
	int *p;
	printf("%d\n",getpid());
	p=mmap(0,4,PROT_READ|PROT_WRITE,
				MAP_ANONYMOUS|MAP_SHARED,0,0);
	if(!p) printf("内存分配失败!\n"),	exit(-1);
	
	printf("分配OK:%p\n",p);
	*p=30;
	*(p+1)=40;
	sleep(20);
	munmap(p,4);	
	printf("释放OK！\n");
	while(1);
	//*p=999;
}
