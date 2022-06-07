#include "minishell.h"

char	*write_redir(char *str, int *ind)
{
	char	*res;
	int		i;

	i = 0;
	if (str[i] == '>')
	{
		i++;
		if (str[i] == '>')
			i++;
	}
	else if (str[i] == '<')
	{
		i++;
		if (str[i] == '<')
			i++;
	}
	res = ft_substr(str, 0, i);
	*ind += i;
	return (res);
}

char	*write_words(char *str, int *ind)
{
	char	*res;
	int		i;

	i = 0;
	res = str;



	*ind += i;
	return (res);
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
	split_by_words = (char **)malloc((words + 1) * sizeof(char *));
	if (!split_by_words)
		exit(1);
	while(str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '|')
			split_by_words[j++] = ft_substr(&str[i++], 0, 1);
		else if (str[i] == '<' || str[i] == '>')
			split_by_words[j++] = write_redir(&str[i], &i);
		else if (str[i + 1] && (!ft_strncmp(&str[i], "\'\'", 2) || !ft_strncmp(&str[i], "\"\"", 2)))
			i += 2;
		else
			i++;
			// split_by_words[j++] = write_words(&str[i], &i);
	}
	split_by_words[j] = NULL;
	return (split_by_words);
}

