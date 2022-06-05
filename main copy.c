/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcherrie <mcherrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:48:58 by marlean           #+#    #+#             */
/*   Updated: 2022/06/05 18:09:47 by mcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_envp	*envp_list;
	t_com	*com;
	char	*read_str;
	// char	**split_words;

	envp_list = NULL;
	// split_words = NULL;
	com = NULL;
	read_envp(env, &envp_list); // в envp_list записаны переменные окружения в односвязном списке
	read_commands(&com); //создан односвязный список из 3 листов (3 команды), изменять вручную
	signal_handler(); //обработка сигналов

	while (1)
	{
		read_str = read_the_line();
		if (ft_strlen(read_str) > 0)
		{
			add_history(read_str);
			check_syntax(&read_str);
		}
		//все функции вставлять сюда:

		replace_dollar(read_str, envp_list);
		char **arr;
		arr = malloc(100);
		arr[0] = "cm1";
		arr[1] = "ar1";
		arr[2] = "0";
		arr[3] = "cm2";
		arr[4] = "ar2";
		arr[5] = "|";
		arr[6] = ">>";
		arr[7] = "ar3";
		com = make_struct(arr);
		// split_words = split_by_words(read_str); //Разбиваем строку на отдельные слова и спец символы

	}
	rl_clear_history();
	return (0);
}

//Разбиваем строку на отдельные слова
//(спец символы |><, все внутри кавычек,
//символы отделенные разными пробелами).
//Сохранять в массив строк (кавычки удаляем)
