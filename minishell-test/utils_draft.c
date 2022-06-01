/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:23:13 by marlean           #+#    #+#             */
/*   Updated: 2022/06/01 19:41:05 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_commands(t_com **com)
{
	//("cat lol.c | cat > lol.c") команда из чеклиста разбивается на список из 3 листов
	t_com	*new;
	// t_com	*tmp;

	// tmp = com;
	*com = com_new("cat", "", "lol.c", "|");
	new = com_new("cat", "", "", ">");
	com_add_back(com, new);
	new = com_new("lol.c", "", "", "");
	com_add_back(com, new);

}

t_com	*com_new(char *name, char *flag, char *arg, char *delim)
{
	t_com	*com;

	com = malloc(sizeof(t_com));
	if (!com)
		return (NULL);
	com->name = name;
	com->flag = flag;
	com->arg = arg;
	com->delim = delim;
	com->next = NULL;
	return (com);
}

void	com_add_back(t_com **lst, t_com *new)
{
	t_com	*elem;

	elem = *lst;
	if (elem)
	{
		while (elem->next)
			elem = elem->next;
		elem->next = new;
	}
	else
		*lst = new;
}
