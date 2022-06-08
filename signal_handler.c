#include "minishell.h"

void	ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	signal_handler(void)
{
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
