/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcherrie <mcherrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:55:14 by mcherrie          #+#    #+#             */
/*   Updated: 2022/06/09 17:17:02 by mcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com	*com_new1(char *name, char **arr, int delim, char *file)
{
	t_com	*com;
	int		i;

	com = malloc(sizeof(t_com));
	if (!com)
		return (NULL);
	com->name = ft_substr(name, 0, 100);
	if (arr)
	{
		i = 0;
		while (arr[i])
			i++;
		com->arg = malloc(sizeof(char *) * i + 1);
		com->arg[i] = NULL;
		i = -1;
		while (arr[++i])
			com->arg[i] = ft_substr(arr[i], 0, 100);
	}
	else
		com->arg = NULL;
	com->delim = delim;
	com->file = ft_substr(file, 0, 100);
	com->next = NULL;
	return (com);
}

void	ft_one_name(t_com	**com)
{
	t_com	*tmp;
	int		first_name;

	tmp = *com;
	first_name = 1;
	while ((*com))
	{
		if (first_name && (*com)->name != NULL)
			first_name = 0;
		else
		{
			printf("Check name = %s\n", (*com)->name);
			add_first_str_in_arr(&(*com)->arg, (*com)->name);
			(*com)->name = NULL;
		}
		if ((*com)->delim == 1)
			first_name = 1;
		(*com) = (*com)->next;
	}
	// if (!first_name)
	// {
	// 	add_first_str_in_arr(&(*com)->arg, (*com)->name);
	// 	(*com)->name = NULL;
	// }
	*com = tmp;
}

int	make_arg(char ***arg, char **arr, int i)
{
	char	**tmp;
	int		n;
	int		j;

	j = 0;
	n = ft_n_words(arr, i);
	if (n == 0)
	{
		*arg = NULL;
		return (0);
	}
	tmp = malloc(sizeof(char *) * (n + 1));
	while (j < n)
		tmp[j++] = ft_substr(arr[i++], 0, 100);
	tmp[j] = NULL;
	*arg = tmp;
	return (n);
}

int	make_new_com(int i, char **arr, t_com	**new_com)
{
	char	*name;
	char	**arg;

	name = ft_substr(arr[i++], 0, 100);
	i = i + make_arg(&arg, arr, i);
	if (arr[i] && delimetr(arr[i]) > 1)
	{
		*new_com = com_new1(name, arg, delimetr(arr[i]), arr[i + 1]);
		i = i + 2;
	}
	else if (arr[i] && delimetr(arr[i]) == 1)
	{
		i++;
		*new_com = com_new1(name, arg, 1, 0);
	}
	else
		*new_com = com_new1(name, arg, 0, 0);
	return (i);
}

void	make_struct(char **arr, t_com	**com)
{
	t_com	*new_com;
	int		i;

	i = 0;
	while (arr[i])
	{
		if (ft_isdelim(arr[i]) && arr[i][0] != '|')
		{
			new_com = com_new1(NULL, NULL, delimetr(arr[i]), arr[i + 1]);
			i += 2;
		}
		else if (ft_isdelim(arr[i]) && arr[i][0] == '|')
		{
			new_com = com_new1(0, 0, 1, 0);
			i++;
		}
		else
			i = make_new_com(i, arr, &new_com);
		com_add_back(com, new_com);
	}
	*com = (*com)->next;
//	ft_lstprint(com);
	ft_one_name(com);
	ft_lstprint(com);
}
//> 1 echo 333 | name 345 > 3 678 > 1 444 555 | name 666 >> 3 777
//> 1 echo 333 | $PWD $SHELL > 3 "678 |  " > 1 444 '$PWD' | name " 666 $a 7" >> 3 777
