/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:07:27 by rdanyell          #+#    #+#             */
/*   Updated: 2022/06/14 11:06:03 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	std_out_close(int save_stdout)
{
	close(0);
	dup2(save_stdout, 0);
	close(save_stdout);
}

static void	pipe_close(t_com *com, int fd0, int fd1)
{
	if (com->next)
	{
		dup2(fd0, 0);
		close(fd0);
		close(fd1);
	}
}

void	pipex(t_com *com, t_envp **env, t_exec *exec)
{
	int	pid;
	int	pipefd[2];
	int	exit_status;

	//printf("i am in pipex\n");
	if(com->delim != 0)
		pipe(pipefd);
	pid = fork();
	// if (pid < 0)
	// 	perror("fork error\n");
	if (pid == 0)
	{
		if (com->next || com->delim == 1)
		{
			//printf("i am in pipex child\n");
			close(1);
			dup2(pipefd[1], 1);
			close(pipefd[1]);
			close(pipefd[0]);
		}
		//printf("Before redirect\n");
		redirect_handler(com);
		executor(com, env, exec);
		exit(0); // статус выхода в этом случае должен говорить об ошибке?
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
	// waitpid(pid, NULL, 0);
	//printf("pipex parrent\n");
	close (0);
	pipe_close(com, pipefd[0], pipefd[1]);
}

// static void	status_handler(t_com *tmp)
// {
// 	int			exits;

// 	while (tmp)
// 	{
// 		wait(&exits);
// 		if (WIFSIGNALED(exits))
// 		{
// 			if (WTERMSIG(exits) != 13)
// 				g_variable.g_exites = 128 + WTERMSIG(exits);
// 			if (WTERMSIG(exits) == SIGQUIT)
// 				printf(" Quit\n");
// 		}
// 		else
// 			g_variable.g_exites = WEXITSTATUS(exits);
// 		tmp = tmp->next;
// 	}
// }

void	pipe_handler(t_com *com, t_envp **env, t_exec *exec)
{
	int		save_stdout;
	int		i;
	t_com	*tmp;

	save_stdout = dup(0);
	tmp = com;
	exec->pipe_num = count_pipes(com);
	//printf("pipe num : %d\n", exec->pipe_num);
	i = 0;
	while (tmp && i <= exec->pipe_num)
	//нужно ли делать двойник чтобы идти по списку? 
	{
		printf("tmp->name %s\n", tmp->name);
		pipex(tmp, env, exec);
		//printf("making pipe\n");
		if ((exec->pipe_num) > 0)
		{
			if (tmp->delim && tmp->delim != 1)
			{
				printf("Hello\n");
				while (tmp->delim && tmp->delim != 1 && tmp->next)
				{
					printf("delim\n");
					tmp = tmp->next;
				}
				if (tmp->delim == 1 && !tmp->name) //пролистывваем пустой список с пайпом
					tmp = tmp->next;
				printf("Goodbye\n");
			}
			else 
				tmp = tmp->next;
			printf("Endof if\n");
		}
		i++;
	}
	tmp = com;
	printf("End of pipe handler\n");
	//status_handler(tmp); //что происходит тут?;
	std_out_close(save_stdout);
}
