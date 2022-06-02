/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:48:58 by marlean           #+#    #+#             */
/*   Updated: 2022/06/02 17:41:52 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_envp	*envp_list;
	t_com	*com;

	envp_list = NULL;
	com = NULL;
	read_envp(env, &envp_list); // в envp_list записаны переменные окружения в односвязном списке
	// read_commands(&com); //создан односвязный список из 3 листов (3 команды), изменять вручную
	signal_handler();

	while (1)
	{
		char	*str;

		str = readline("Myshell 🐚 ");
		if (!str)
		{
			printf("exit");
			exit(1);
		}
		add_history(str);
		free(str);
	}

	return (0);
}