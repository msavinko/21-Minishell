/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:15:18 by rdanyell          #+#    #+#             */
/*   Updated: 2022/06/17 13:26:02 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize(t_com *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst)
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}

int	envsize(t_envp *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst)
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}

int	count_array(t_com *com)
{
	int	i;

	i = 0;
	while (com->arg[i])
		i++;
	return (i);
}

int	count_pipes(t_com *com)
{
	t_com	*command;
	int		pipes;

	pipes = 0;
	command = com;
	while (command)
	{
		if (command->delim == 1)
			pipes++;
		command = command->next;
	}
	return (pipes);
}
