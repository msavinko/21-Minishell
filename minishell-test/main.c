/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:24:33 by marlean           #+#    #+#             */
/*   Updated: 2022/06/01 19:44:09 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_envp	*envp_list;
	t_com	*com;

	envp_list = NULL;
	com = NULL;
	read_envp(env, envp_list); // в envp_list записаны переменные окружения в односвязном списке
	read_commands(&com); //создан односвязный список из 3 листов (3 команды), изменять вручную
	return (0);
}