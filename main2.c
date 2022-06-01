/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:43:59 by marlean           #+#    #+#             */
/*   Updated: 2022/06/01 14:41:27 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	rl_outstream = stderr;
	while (1)
	{
		char *str = readline("Myshell 🐚 ");
		printf("read this string ->|%s|<-\n", str);
		add_history(str);
		free(str);
	}
	return (0);
}