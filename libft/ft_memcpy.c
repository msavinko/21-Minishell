/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:07:13 by marlean           #+#    #+#             */
/*   Updated: 2021/10/21 10:48:07 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t n)
{
	char			*result;
	char			*original;
	unsigned int	i;

	if (!dest && !source)
		return (NULL);
	i = 0;
	result = (char *)dest;
	original = (char *)source;
	while (i < n)
	{
		result[i] = original[i];
		i++;
	}
	return (result);
}
