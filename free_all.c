#include "minishell.h"

void ft_clear_struct(t_com **com)
{
	t_com *tmp;

	if (com && *com)
	{
		while (*com)
		{
			tmp = (*com)->next;
			if ((*com)->name)
				free((*com)->name);
			if ((*com)->arg)
				ft_clear_arr((*com)->arg);
			if ((*com)->file)
				free((*com)->file);
			free(*com);
			*com = tmp;
		}
	}
}

void ft_clear_arr(char **arr)
{
	int i;
	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void free_envp_list(t_envp *envp_list)
{
	if (!envp_list)
		return;
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

void error_double_delim(char *read_str)
{
	printf("syntax error near unexpected token `newline'");
	free(read_str);
	rl_clear_history();
	exit(1);
}
