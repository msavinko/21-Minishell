/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:00:15 by mcherrie          #+#    #+#             */
/*   Updated: 2022/06/10 19:52:03 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_arr(char **arr_in, char **arr_out)
{
	int	i;

	i = 0;
	while (arr_out[i])
		i++;
	arr_in = malloc(sizeof(char *) * i + 1);
	arr_in[i] = NULL;
	i = -1;
	while (arr_out[++i])
		arr_in[i] = ft_substr(arr_out[i], 0, 100);
}

int	ft_n_words(char **arr, int i)
{
	int	n;

	n = 0;
	while (arr[i] && !ft_isdelim(arr[i++]))
		n++;
	return (n);
}

void	ft_empty_arr(char ***tmp, char *str)
{
	*tmp = (char **)malloc(sizeof(char *) * 2);
	(*tmp)[0] = ft_substr(str, 0, 1000);
	(*tmp)[1] = NULL;
}

void	add_first_str_in_arr(char ***arr, char *str)
{
	char	**tmp;
	int		i;

	tmp = *arr;
	i = 0;
	if (*arr)
	{
		while ((*arr)[i])
			i++;
		tmp = malloc(sizeof(char *) * (i + 2));
		tmp[i + 1] = NULL;
		tmp[0] = ft_substr(str, 0, 100);
		i = 0;
		while ((*arr)[i])
		{
			tmp[i + 1] = ft_substr((*arr)[i], 0, 1000);
			i++;
		}
	}
	else
		ft_empty_arr(&tmp, str);
	*arr = tmp;
}

void	ft_lstprint(t_com **com)
{
	t_com	*tmp;
	int		i;

	tmp = *com;
	while ((*com))
	{
		i = 0;
		printf("name = %s delim = %d file = %s\n", (*com)->name, (*com)->delim, (*com)->file);
		if ((*com)->arg)
		{
			printf("OK\n");
			while ((*com)->arg[i])
			{
				printf("arg[%d] = %s \n", i, (*com)->arg[i]);
				i++;
			}
		}
		*com = (*com)->next;
	}
	// printf("name = %s delim = %d file = %s\n", (*com)->name, (*com)->delim, (*com)->file);
	// i = 0;
	// if ((*com)->arg)
	// 	while ((*com)->arg[i])
	// 	{
	// 		printf("arg[%d] = %s \n", i, (*com)->arg[i]);
	// 		i++;
	// 	}
	*com = tmp;
}