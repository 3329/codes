#include <stdio.h>

int main(int argc,char **argv)
{
    unsigned char attr[]={0,1,4,5,7,8};
    unsigned char fore[]={30,31,32,33,34,35,36,37};
    unsigned char back[]={40,41,42,43,44,45,46,47};
    int adx,fdx,bdx;

    for(bdx=0;bdx <sizeof(back);bdx++)
    {
        for(fdx=0;fdx <sizeof(fore);fdx++)
        {
            for(adx=0;adx <sizeof(attr);adx++)
            {
                printf("\033[%d;%d;%dmhello,NSFocus!!!\033[0m",
                    attr[adx],fore[fdx],back[bdx]);
                printf("<==attr=%d,fore=%d,back=%d\n",
                    attr[adx],fore[fdx],back[bdx]);
            }
        }
        printf("\n");
    }
}
