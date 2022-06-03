/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:10:55 by marlean           #+#    #+#             */
/*   Updated: 2022/06/03 11:24:58 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

# define WHITE_SPACES " \t\v\r\f"

int	g_exit_code;

typedef struct	s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct	s_command
{
	char				*name;
	char				*flag;
	char				*arg;
	char				*delim;
	struct s_command	*next;
}	t_com;

//list_utils.c
t_envp	*envp_new(char *content);
void	read_envp(char **env, t_envp **envp_list);
void	envp_add_front(t_envp **lst, t_envp *new);

//signal_handler.c
int		signal_handler();
void	ctrl_c_handler(int signum);

//utils_draft
void	read_commands(t_com **com);
t_com	*com_new(char *name, char *flag, char *arg, char *delim);
void	com_add_back(t_com **lst, t_com *new);

//check_sytax.c
void	check_syntax(char **str);
// int	check_syntax(char *str);

int	ft_check_first_end(char **str);
int	ft_check_eve_quotes(char *str);


#endif