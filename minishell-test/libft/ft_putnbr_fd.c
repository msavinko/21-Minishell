/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:41:48 by marlean           #+#    #+#             */
/*   Updated: 2021/10/25 15:59:44 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int		count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	ft_minmax(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n == 2147483647)
		ft_putstr_fd("2147483647", fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		count;
	char	num[10];

	if (n == -2147483648 || n == 2147483647)
	{
		ft_minmax(n, fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= (-1);
	}
	count = ft_count(n);
	while (count > 0)
	{	
		num[count - 1] = (n % 10) + '0';
		n = n / 10;
		count--;
	}
	ft_putstr_fd(num, fd);
}
