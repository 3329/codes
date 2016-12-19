#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/poll.h>
#include <getopt.h>
#include <readline/readline.h>
#include <readline/history.h>


#define READLINE_PROMPT "command->"
#define MAX_COMMAND_LINE_LENGTH 1024

int print_help()
{
	printf("option command... \n\
				              \n");
	return 0;
}

int is_command_line(char *command)
{
    char *p = command;
    
    if (p == NULL)
    {
        return 0;
    }

    while (*p == ' ' || *p == '\t' || *p == '\n')
    {
        p++;
    }

    if (*p == '#' || *p == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int command_handler(char *pCommandLine)
{
    int Ret = 0;
    char Param[20][30];
    char *pToken = NULL;
    int i =0;
    int Address = 0;
    int Value = 0;

    if (0 == is_command_line(pCommandLine))
    {
        printf("invalid command or parameter\n ");
        print_help();
        return 1;
    }

    pToken = strtok(pCommandLine, " \t\n\r");
	for(i =0; pToken != NULL&& i<16;i++ )
    {
  		if((strlen(pToken) > 28) || (*pToken == '\0'))
       	{
    	    printf("invalid command or parameter\n ");
            print_help();
            return 0;
		}
		strcpy(Param[i],pToken);
  	 	pToken = strtok(NULL," \t\n\r");
  	}

	if(0 == strcmp(Param[0],"read"))
	{
        if(0 == strcmp(Param[1],"\0"))
        {
            printf("invalid conmmand or parameter\n");
            return -1;
        }

        Address = strtol(Param[1],NULL,16);
        Ret = xxxx_read(Address,&Value);
        if(Ret != 0)
        {
            printf("xxxx read eroor\n");
            return -1;
        }
        printf("xxxx read 0x%x , 0x%x\n", Address, Value);
	}
    else if(0 == strcmp(Param[0],"q"))
    {
        exit(0);
    }
    else
    {
	    printf("invalid command or parameter\n ");
        print_help();
        return -1;
    }
    return 0;
}

int main()
{
    char *pReadLine = NULL;
    char CommandLine[MAX_COMMAND_LINE_LENGTH] = {0};
    int Ret = -1;

    print_help();

    while(1)
    {
        pReadLine = readline(READLINE_PROMPT);
        if (pReadLine && *pReadLine && strlen(pReadLine) < MAX_COMMAND_LINE_LENGTH - 1)
        {
            strcpy(CommandLine, pReadLine);
        }
        else if (strlen(pReadLine) >= MAX_COMMAND_LINE_LENGTH - 1)
        {
            printf("   -- Error: Too long command line!\n");
            continue;
        }

        Ret = command_handler(CommandLine);
        if (0 == Ret)
        {
            add_history(pReadLine);

            if (pReadLine != NULL)
            {
                free(pReadLine);
                pReadLine = NULL;
                CommandLine[0] = 0;
            }
        }
    }

    return 0;
}





