/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:15:23 by marlean           #+#    #+#             */
/*   Updated: 2022/06/02 16:46:11 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_handler(int sig)
{
	printf("\n");
	// (void)sig;
	g_exit_code = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();

}

int	signal_handler(void)
{
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}