
#include "minishell.h"

int write_symb(char **res, char *str)
{
	int i;

	i = 0;
	while (str[i] && !ft_separator(str[i]))
		i++;
	*res = ft_substr(str, 0, i);
	printf("res symb: %s\n", *res);
	return (i);
}

int in_quotes(int quotes, char **res, char *str)
{
	int i;

	i = 1;
	if (quotes == SIN_Q)
	{
		while (str[i] && str[i] != '\'')
			i++;
	}
	else if (quotes == DOUB_Q)
	{
		while (str[i] && str[i] != '\"')
			i++;
	}
	*res = ft_substr(str, 1, i - 1);
	printf("res: %s\n", *res);
	return (i + 1);
}

int write_redir(char **res, char *str)
{
	int i;

	i = 0;
	if (str[i] == '<')
	{
		if (str[i + 1] && str[i + 1] == '<')
			i++;
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] && str[i + 1] == '>')
			i++;
	}
	i++;
	*res = ft_substr(str, 0, i);
	return (i);
}

char **split_by_words(char *str)
{
	char **split_by_words;
	int i;
	int words;
	int j;

	i = 0;
	j = 0;
	words = count_words(str, i, 0);
	printf("words start: %d\n", words);
	split_by_words = (char **)malloc((words + 1) * sizeof(char *));
	if (!split_by_words)
		exit(1);
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '\'')
		{
			if (str[i + 1] && str[i + 1] == '\'')
				i += 2;
			else
				i += in_quotes(SIN_Q, &split_by_words[j++], &str[i]);
		}
		else if (str[i] == '\"')
		{
			if (str[i + 1] && str[i + 1] == '\"')
				i += 2;
			else
				i += in_quotes(DOUB_Q, &split_by_words[j++], &str[i]);
		}
		else if (str[i] == '|')
			split_by_words[j++] = ft_substr(&str[i++], 0, 1);
		else if (str[i] == '<' || str[i] == '>')
			i += write_redir(&split_by_words[j++], &str[i]);
		else if (str[i] && !ft_separator(str[i]))
			i += write_symb(&split_by_words[j++], &str[i]);
		else
			i++;
	}
	split_by_words[j] = NULL;
	return (split_by_words);
}