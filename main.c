/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:48:58 by marlean           #+#    #+#             */
/*   Updated: 2022/06/03 11:45:49 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*read_the_line(void)
// {
// 	char	*read_str;

// 	read_str = readline("Myshell 🐚 ");
// 	if (!read_str)
// 	{
// 		printf("exit");
// 		g_exit_code = 1;
// 		// rl_clear_history();
// 		// free(read_str);
// 		exit(g_exit_code);
// 	}
// 	// free(read_str);
// 	add_history(read_str);
// 	return (read_str);
// }


int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_envp	*envp_list;
	t_com	*com;
	char	*read_str;

	envp_list = NULL;
	g_exit_code = -1;
	com = NULL;
	read_envp(env, &envp_list); // в envp_list записаны переменные окружения в односвязном списке
	read_commands(&com); //создан односвязный список из 3 листов (3 команды), изменять вручную
	signal_handler(); //обработка сигналов

	while (1)
	{
		read_str = readline("Myshell 🐚 ");
		if (!read_str)
		{
			printf("exit");
			rl_clear_history();
			exit(1);
		}
		signal_handler();

		if (ft_strlen(read_str) > 0)
		{
			add_history(read_str);
			check_syntax(&read_str);
		}
		printf("str: |%s|\n", read_str);

		// free(read_str);
	}
	rl_clear_history();
	return (0);
}