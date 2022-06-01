/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 09:49:49 by marlean           #+#    #+#             */
/*   Updated: 2021/10/27 11:11:12 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*addr_of_next_el;

	while (*lst)
	{
		addr_of_next_el = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = addr_of_next_el;
	}
	*lst = NULL;
}
