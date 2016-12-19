#include <stdio.h>
int main()
{
	/*ÄÚÖÃµÄºê*/
	printf("%s\n",__BASE_FILE__);
	printf("%s\n",__DATE__);
	printf("%s:%s\n",__FUNCTION__,__func__);
	printf("%d\n",__LINE__);
#ifdef __cplusplus
	printf("%d\n",__cplusplus);
#endif
	return 0;
}
