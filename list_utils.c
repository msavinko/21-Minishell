/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariasavinova <mariasavinova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/16 12:08:23 by mariasavino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_the_line(void)
{
	char *read_str;

	read_str = readline("Myshell 🐚 ");
	if (!read_str)
	{
		printf("exit\n");
		rl_clear_history();
		exit(1);
	}
	return (read_str);
}

void read_envp(char **env, t_envp **envp_list)
{
	int i;
	int flag;
	t_envp *new;

	i = 0;
	flag = 0;
	*envp_list = envp_new(env[i++]);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "EXIT_STATUS=", 12))
			flag = 1;
		new = envp_new(env[i]);
		envp_add_front(envp_list, new);
		i++;
	}
	if (!flag)
	{
		new = envp_new("EXIT_STATUS=0");
		envp_add_front(envp_list, new);
	}
}

t_envp *envp_new(char *content)
{
	t_envp *envp;
	int i;
	int len;

	i = 0;
	envp = malloc(sizeof(t_envp));
	if (!envp)
		return (NULL);
	len = ft_strlen(content);
	while (content[i] != '=')
		i++;
	envp->key = malloc(sizeof(char) * (i + 1));
	envp->value = malloc(sizeof(char) * (len - i + 1));
	if (!envp->key || !envp->value)
		return (NULL);
	ft_strlcpy(envp->key, content, i + 1);
	ft_strlcpy(envp->value, &content[i + 1], len - i);
	envp->next = NULL;
	return (envp);
}

void envp_add_front(t_envp **lst, t_envp *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
