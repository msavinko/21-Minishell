/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:20:13 by marlean           #+#    #+#             */
/*   Updated: 2021/10/21 17:03:15 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t n)
{
	unsigned int	i;
	char			*result;
	char			*original;

	if (!dest && !source)
		return (NULL);
	i = 0;
	result = (char *)dest;
	original = (char *)source;
	if (dest < source)
	{
		while (i < n)
		{
			result[i] = original[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			result[n] = original[n];
	}
	return (result);
}
