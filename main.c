/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:18:54 by rdanyell          #+#    #+#             */
/*   Updated: 2022/06/17 13:26:17 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_args(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_putstr_fd("Myshell 🐚: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
}

void	parse_and_execute(t_envp **envp_list, t_com *com, char **split_words)
{
	char	*read_str;

	read_str = read_the_line();
	if (ft_strlen(read_str) > 0)
	{
		add_history(read_str);
		if (!check_syntax(read_str))
		{
			replace_dollar(&read_str, *envp_list);
			split_words = split_by_words(read_str);
			if (split_words != NULL && split_words[0] != NULL)
			{
				if (check_double_delim(split_words))
					ft_putendl_fd("syntax error near \
									unexpected token `newline'", 2);
				make_struct(split_words, &com);
				if (com)
					execute(com, envp_list);
			}
		}
		ft_free_com_list(&com);
		free_array(split_words);
		free(read_str);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**split_words;
	t_envp	*envp_list;
	t_com	*com;

	check_args(argc, argv);
	g_exit_status = 0;
	split_words = NULL;
	envp_list = NULL;
	com = NULL;
	read_envp(env, &envp_list);
	signal_handler();
	while (1)
		parse_and_execute(&envp_list, com, split_words);
	rl_clear_history();
	return (0);
}
