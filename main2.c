/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:24:33 by marlean           #+#    #+#             */
/*   Updated: 2022/06/03 11:03:59 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

int	ft_check_eve_quotes(char *str)
{
	int		count_one;
	int		count_double;

	count_one = 0;
	count_double = 0;
	while (*str)
	{
		if (*str == '\'' && count_double % 2 == 0)
			count_one++;
		if (*str == '\"' && count_one % 2 == 0)
			count_double++;
		str++;
	}
		if (count_double % 2 == 0 && count_one % 2 == 0)
			return (0);
		else
			return (1);
}

int	ft_check_first_end(char *str)
{
	char	*tmp;

	tmp = str;
	tmp = ft_strtrim(tmp, WHITE_SPACES);
	printf("s = #%s#", tmp);
	if (*tmp == '|' || *tmp == '<' || *tmp == '>')
		return(1);
	while(*tmp)
		tmp++;
	tmp--;
	if (*tmp == '|' || *tmp == '<' || *tmp == '>')
		return(1);
	return(0);
}

int	check_syntax(char *str)
{
	if (!ft_strlen(str) || ft_check_eve_quotes(str) \
		|| ft_check_first_end(str))
		printf("sintax dont ok\n");
	//	return(1);//надо прописать поведение
	else
		printf("sintax ok\n");
	return(0);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_envp	*envp_list;
	t_com	*com;

	envp_list = NULL;
	com = NULL;
	read_envp(env, &envp_list); // в envp_list записаны переменные окружения в односвязном списке
	read_commands(&com); //создан односвязный список из 3 листов (3 команды), изменять вручную
	while (1)
	{
		char *str = readline("Myshell 🐚 ");
		if (!str)
			return(1);//надо прописать поведение

		if (check_syntax(str))
			return(1);//надо прописать поведение
//		printf("str = %s\n", str);
		add_history(str);
		free(str);
	}
	return (0);
}
