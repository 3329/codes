#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
  
int main()
{
    char* input, shell_prompt[100];
  
    // Configure readline to auto-complete paths when the tab key is hit.
    rl_bind_key('\t', rl_complete);
	char* tips = "AOS>";
	char* nextTips = "  ->";
  
	//int i = 0;
    for(;;) {
        snprintf(shell_prompt, sizeof(shell_prompt), "%s ", tips);
        input = readline(shell_prompt);
		printf("%s\n", input);

        // Check for EOF.
        if (!input) break;
		if (strncmp("exit", input, 4) == 0)
		{
			printf("Bye\n");
			exit(0);
		}

        // Add input to history.
        add_history(input);
  
        // Do stuff...
  
        // Free input.
        free(input);
    }
}
