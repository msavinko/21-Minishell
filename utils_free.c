#include "minishell.h"

void	free_envp_list(t_envp *envp_list)
{
	if (!envp_list)
		return ;
	while (envp_list)
	{
		if (envp_list->key)
			free(envp_list->key);
		if (envp_list->value)
			free(envp_list->value);
		envp_list = envp_list->next;
	}
	free(envp_list);
	envp_list = NULL;
}

void	free_com_list(t_com *com)
{
	int	i;

	if (!com)
		return ;
	while (com)
	{
		i = 0;
		while (com->arg[i])
			free(com->arg[i++]);
		if (com->arg)
			free(com->arg);
		com = com->next;
	}
	free(com);
	com = NULL;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	ft_free(char *str)
{
	if (str)
		free(str);
}