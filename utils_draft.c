#include "minishell.h"

void	read_commands(t_com **com)
{
	t_com	*new;
	char	**arg;

	arg = (char **)malloc((15) * sizeof(char *));
	arg[0] = "lol.c";
	*com = com_new("cat", arg, PIPE);
	arg[0] = "";
	new = com_new("cat", arg, RIGH_SIN_REDIR);
	com_add_back(com, new);
	arg[0] = "";
	new = com_new("lol.c", arg, 0);
	com_add_back(com, new);
}

t_com	*com_new(char *name, char **arg, int delim)
{
	t_com	*com;

	com = malloc(sizeof(t_com));
	if (!com)
		return (NULL);
	com->name = name;
	com->arg = arg;
	com->delim = delim;
	com->next = NULL;
	return (com);
}

void	com_add_back(t_com **lst, t_com *new)
{
	t_com	*elem;

	elem = *lst;
	if (elem)
	{
		while (elem->next)
			elem = elem->next;
		elem->next = new;
	}
	else
		*lst = new;
}
