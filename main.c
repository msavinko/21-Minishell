#include "minishell.h"

int	g_exit_code;

void	read_envp(char **env, t_envp *envp_list)
{
	int	i;
	t_envp	*new;

	i = 0;
	envp_list = envp_new(env[i++]);
	while (env[i])
	{
		new = envp_new(env[i++]);
		envp_add_front(&envp_list, new);

	}
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;


	// char	**command;
	t_envp	*envp_list;

	envp_list = NULL;
	// while (1)
	// {
		read_envp(env, envp_list);

	// }
	return (0);
}