/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:26:39 by marlean           #+#    #+#             */
/*   Updated: 2022/02/18 11:03:51 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long int num)
{
	int	len;

	len = 0;
	if (num < 0)
	{
		num *= -1;
		len++;
	}
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(long int num)
{
	char				*str;
	int					len;

	len = ft_len(num);
	if (num == 0)
		len = 1;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		if ((num % 10) > 9)
			str[len - 1] = (num % 10) + 'a' - 10;
		else
			str[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (str);
}
