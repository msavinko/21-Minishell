/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:50:32 by marlean           #+#    #+#             */
/*   Updated: 2021/10/22 10:36:26 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*array;

	i = 0;
	array = (char *)s;
	while (i < n)
	{
		if (array[i] == (char)c)
			return (&array[i]);
		i++;
	}
	return (NULL);
}
