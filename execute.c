/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:18:54 by rdanyell          #+#    #+#             */
/*   Updated: 2022/06/15 13:26:43 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_handler(t_com *com, t_exec *exec)
{
	int	exit_status;
	int	pid;
	
	make_full_com(com, exec);
	// printf("exec->cmd_exec: %s\n", exec->cmd_exec);
	// printf("exec->cmd_full[0]: %s\n", exec->cmd_full[0]);
	// printf("exec->cmd_full[1]: %s\n", exec->cmd_full[1]);
	pid = fork();
	if (pid == 0)
	{
		execve(exec->cmd_exec, exec->cmd_full, exec->env);
		ft_putstr_fd("Myshell 🐚: ", 2);
		ft_putstr_fd(exec->cmd_full[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
	wait(&exit_status);
	if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) != 13)
			g_exit_status = 128 + WTERMSIG(exit_status);
		if (WTERMSIG(exit_status) == SIGQUIT)
			ft_putendl_fd("Quit", 2);
	}
	else
		g_exit_status = WEXITSTATUS(exit_status);
	// if (exec->path)
	// 	free(exec->path);
	// if (exec->path_cmd)
	// 	ft_clear_arr(exec->path_cmd);
	// if (exec->cmd_full)
	// 	free(exec->cmd_full);
	// if (exec->cmd_exec)
	// 	free(exec->cmd_exec);
	// if (exec->env)
	// 	free(exec->env);
}

void	executor(t_com *com, t_envp **envp_list, t_exec *exec)
{
	if (!ft_strcmp(com->name, "echo") || !ft_strcmp(com->name, "ECHO"))
		g_exit_status = builtin_echo(com);
	else if (!ft_strcmp(com->name, "env") || !ft_strcmp(com->name, "ENV"))
		g_exit_status = builtin_env(*envp_list);
	else if (!ft_strcmp(com->name, "pwd") || !ft_strcmp(com->name, "PWD"))
		g_exit_status = builtin_pwd(*envp_list);
	else if (!ft_strcmp(com->name, "unset"))
		g_exit_status = builtin_unset(com, envp_list);
	else if (!ft_strcmp(com->name, "export"))
		g_exit_status = builtin_export(com, envp_list);
	else if (!ft_strcmp(com->name, "cd"))
		g_exit_status = builtin_cd(com, *envp_list);
	else if (!ft_strcmp(com->name, "exit"))
		builtin_exit(com);
		// builtin_exit(com, *envp_list);
	else
	{
		get_env(*envp_list, exec);
		execve_handler(com, exec);
	}
}

void	execute(t_com *com, t_envp **env)
{
	t_exec	exec;

	//printf("EXECUTION\n");
	g_exit_status = 1;
	if (com->delim != 0)
		pipe_handler(com, env, &exec);
	else
		executor(com, env, &exec);
	g_exit_status = 0;
	//printf("END OF EXECUTION\n");
	//ft_clear_struct(&com);
}
