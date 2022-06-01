/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:37:34 by marlean           #+#    #+#             */
/*   Updated: 2021/10/21 16:55:31 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*res;
	int		len;

	i = 0;
	res = (char *)s;
	len = 0;
	while (res[len])
		len++;
	while (len >= 0)
	{
		if (res[len] == (char)c)
			return (&res[len]);
		len--;
	}
	if (c == '\0')
		return (&res[len]);
	return (NULL);
}
