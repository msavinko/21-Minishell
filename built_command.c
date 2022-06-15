/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:00:45 by rdanyell          #+#    #+#             */
/*   Updated: 2022/06/14 15:41:33 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_cmd(t_com *com, t_exec *exec)
{
	char	*tmp;
	char	*command;
	int		i;

	exec->cmd_full[0] = ft_strdup(com->name);
	i = 0;
	while (exec->path_cmd[i])
	{
		tmp = ft_strjoin(exec->path_cmd[i], "/");
		command = ft_strjoin(tmp, com->name);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	get_env(t_envp *env, t_exec *exec)
{
	t_envp	*envir;
	char	*tmp;
	int		i;

	envir = env;
	while (envir)
	{
		if (ft_strncmp("PATH", envir->key, 4) == 0)
			exec->path = envir->value;
		envir = envir->next;
	}
	exec->path_cmd = ft_split(exec->path, ':');
	i = envsize(env);
	exec->env = (char **)malloc (sizeof(char *) * (i + 2));
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		exec->env[i] = ft_strjoin(tmp, env->value);
		env = env->next;
		i++;
	}
}

void	find_args(t_com *com, t_exec *exec)
{
	int		i;
	int		j;
	t_com	*coms;

	coms = com;
	i = 1;
	j = 0;
	if (coms->delim == 1)
	{
		if (coms->arg)
		{
			while (coms->arg[j])
			{
				exec->cmd_full[i] = ft_strdup(coms->arg[j]);
				i++;
				j++;
			}
		}
		if (!coms->arg)
		{
			exec->cmd_full[1] = (char *)malloc(sizeof(char *));
		}
	}
	while (coms && coms->delim != 1)
	{
		if (coms->arg)
		{
			while (coms->arg[j])
			{
				exec->cmd_full[i] = ft_strdup(coms->arg[j]);
				i++;
				j++;
			}
		}
		j = 0;
		coms = coms->next;
	}
}

void	make_full_com(t_com *com, t_exec *exec)
{
	t_com	*full_com;
	t_com	*com_name;
	int		com_num;

	com_num = 1;
	full_com = com;
	com_name = com;
	while (full_com && full_com->delim != 1)
	{
		full_com = full_com->next;
		com_num++;
	}
	exec->cmd_full = (char **)malloc(sizeof(char *) * (com_num * 10));
	//нужно маллочить под кол-во аргументов, которое мы не знаем
	if (com_name->delim == 0 || com_name->delim == 1)
		check_cmd(com_name, exec);
	while (com_name && com_name->delim != 1)
	{
		if (com_name->name)
		{
			check_cmd(com_name, exec);
			break ;
		}
		com_name = com_name->next;
	}
	find_args(com, exec);
}

void	check_cmd(t_com *com, t_exec *exec)
{
	char	*com_name;
	t_com	*command;

	command = com;
	if (ft_strncmp(command->name, "/", 1) == 0)
	{
		exec->cmd_exec = command->name;
		com_name = ft_strrchr(command->name, '/');
		com_name++;
		exec->cmd_full[0] = ft_strdup(com_name);
	}
	else
	{
		exec->cmd_exec = make_cmd(command, exec);
		if (!exec->cmd_exec)
		{
			exec->cmd_exec = command->name;
			g_exit_status = 127;
		}
	}
}
