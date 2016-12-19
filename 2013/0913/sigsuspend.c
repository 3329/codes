#include <stdio.h>
#include <unistd.h>
#include <signal.h>
main()
{
	int sum = 0;
	int i;
	sigset_t sigs;
	sigset_t psigs;
	sigset_t newsigs;

	sigemptyset(&sigs);
	sigemptyset(&psigs);
	sigfillset(&sigs);
	sigfillset(&newsigs);
	sigdelset(&newsigs, 2);

	// signal mask
	sigprocmask(SIG_BLOCK, &sigs, NULL);
	for (i=0; i<10; i++)
	{
		sum += i;
		sleep(2);
		printf("^O^\n");
		sigpending(&psigs);
		if (sigismember(&psigs, 2))
		{
			//sigsuspend(&newsigs);
			sigprocmask(SIG_UNBLOCK, &sigs, NULL);

			sigprocmask(SIG_BLOCK, &newsigs, NULL);
			// do something
			sigprocmask(SIG_UNBLOCK, &newsigs, NULL);

			sigprocmask(SIG_BLOCK, &sigs, NULL);
		}
	}
	printf("sum = %d\n", sum);
	sigprocmask(SIG_UNBLOCK, &sigs, NULL);
	printf("Over!\n");
}

