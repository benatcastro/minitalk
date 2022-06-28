# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
#include "ft_printf.h"
void signal_handler(int signum, siginfo_t *siginfo, void *ucontext)
{
	if (signum != SIGUSR1) return;
	if (siginfo->si_code != SI_QUEUE) return;

	printf("Server value %d", siginfo->si_int);
}

int main(int argc, char **argv)
{
	struct sigaction s_action;

	ft_printf("SERVER PID: %d\n",getpid);
	s_action.sa_sigaction = signal_handler;
	sigemptyset (&s_action.sa_mask);
	s_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_action, NULL);

	while(1)
		sleep(100);
	return EXIT_SUCCESS;
}
