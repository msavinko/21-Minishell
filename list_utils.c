/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:55:58 by marlean           #+#    #+#             */
/*   Updated: 2022/06/01 19:24:17 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*envp_new(char *content)
{
	t_envp	*envp;
	int		i;
	int		len;

	i = 0;
	envp = malloc(sizeof(t_envp));
	if (!envp)
		return (NULL);
	len = ft_strlen(content);
	while (content[i] != '=')
		i++;
	
	envp->key = malloc (sizeof(char) * (i + 1));
	envp->value = malloc (sizeof(char) * (len - i + 1));
	if (!envp->key || !envp->value)
		return (NULL);
	ft_strlcpy(envp->key, content, i + 1);
	ft_strlcpy(envp->value, &content[i + 1], len - i);
	envp->next = NULL;

	printf("%s=%s\n", envp->key, envp->value);
	return (envp);
}

void	envp_add_front(t_envp **lst, t_envp *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}

	
}