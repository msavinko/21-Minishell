/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:10:55 by marlean           #+#    #+#             */
/*   Updated: 2022/06/02 12:27:26 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"

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

t_envp	*envp_new(char *content);
void	read_envp(char **env, t_envp *envp_list);
void	envp_add_front(t_envp **lst, t_envp *new);

void	read_commands(t_com **com);
t_com	*com_new(char *name, char *flag, char *arg, char *delim);
void	com_add_back(t_com **lst, t_com *new);

#endif