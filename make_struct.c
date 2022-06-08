#include "minishell.h"

t_com *com_new1(char *name, char **arg, int delim)
{
	t_com *com;

	com = malloc(sizeof(t_com));
	if (!com)
		return (NULL);
	com->name = name;
	com->arg = arg;
	com->delim = delim;
	com->next = NULL;
	return (com);
}

// void	com_add_back(t_com **lst, t_com *new) Сейчас она в draft, потом раскомментировать
// {
// 	t_com	*elem;

// 	elem = *lst;
// 	printf("add new list\n");
// 	if (elem)
// 	{
// 		while (elem->next)
// 			elem = elem->next;
// 		elem->next = new;
// 	}
// 	else
// 		*lst = new;
// }

int ft_isdelim(char *s)
{
	if (!ft_strncmp(s, "|", 1) || !ft_strncmp(s, "<", 1) || !ft_strncmp(s, ">", 1) ||
		!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2))
		return (1);
	else
		return (0);
}

int delimetr(char *s)
{
	if (s[0] == '|')
		return (1);
	if (s[0] == '<' && s[1] == '0')
		return (2);
	if (s[0] == '>' && s[1] == '0')
		return (3);
	if (s[0] == '<' && s[1] == '<')
		return (4);
	if (s[0] == '>' && s[1] == '>')
		return (5);
	return (0);
}

void ft_lstprint(t_com **com)
{
	t_com *tmp;

	tmp = *com;
	while (tmp->next != NULL)
	{
		// printf("name = %s delim = %d\n", tmp->name, tmp->delim);
		tmp = tmp->next;
	}
	// printf("name = %s delim = %d\n", tmp->name, tmp->delim);
	//	printf("name = %s args = %s delim = %d\n", tmp->name, tmp->arg[0], tmp->delim);
}

int make_arg(char **arg, char **arr, int i)
{
	int n;
	int j;
	// записывает нуль-детерминированный массив аргументоа и возвращает количество слов в нем
	n = 0;
	j = 0;
	while (arr[i] && !ft_isdelim(arr[i++]))
		n++;
	// printf("n = %d\n", n);
	arg = malloc(sizeof(char *) * n + 1);
	i = i - n - 1;
	while (j < n)
	{
		//		printf("!!!arr[%d] = %s\n", i, arr[i]);
		//		i++;
		arg[j++] = ft_substr(arr[i++], 0, 100);
		// printf("arg[%d] = %s\n", j - 1, arg[j - 1]);
	}
	arg[j] = NULL;
	return (n);
}

t_com *make_struct(char **arr)
{
	t_com *com;
	t_com *new_com;
	char *name;
	char **arg;
	int delim;
	int i;

	com = malloc(sizeof(t_com));
	i = 0;
	while (arr[i])
	{
		if (ft_isdelim(arr[i]))
			new_com = com_new1(0, 0, delimetr(arr[i++]));
		else
		{
			name = arr[i++];
			arg = 0;
			delim = 0;
			if (arr[i] && !ft_isdelim(arr[i]))
				i = i + make_arg(arg, arr, i);
			if (arr[i])
				delim = delimetr(arr[i++]);
			new_com = com_new1(name, arg, delim);
		}
		com_add_back(&com, new_com);
	}
	com = com->next;
	ft_lstprint(&com);
	return (0);
}
