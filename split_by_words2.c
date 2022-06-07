
#include "minishell.h"

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
	printf("res: %s\n", *res);
	return (i);
}

// int	write_words(char **res, char *str)
// {
// 	int	i;
// 	int	count_one;
// 	int	count_double;

// 	i = 0;
// 	count_one = 0;
// 	count_double = 0;
// 	// printf("\nwe received %s\n", str);
// 	while (str[i]) 
// 	{
// 		// printf("|%c|", str[i]);
// 		if (ft_separator(str[i]) && count_one % 2 == 0 && count_double % 2 == 0)
// 		{
// 			*res = ft_substr(str, 0, i);
// 			// printf("res break: |%s| and i: %d\n", *res, i);
// 			return (i);
// 		}
// 		if (str[i] == '\'' && count_double % 2 == 0)
// 			count_one++;
// 		if (str[i] == '\"' && count_one % 2 == 0)
// 			count_double++;
// 		i++;
// 	}
// 	*res = ft_substr(str, 0, i);
// 	// printf("res: %s and i: %d\n", *res, i);
// 	return (i);
// }

int	count_space(char *str)
{
	int	i;
	int	count_one;
	int	count_double;

	i = 0;
	count_one = 0;
	count_double = 0;
	while (i < (int)ft_strlen(str))
	{
		if (ft_separator(str[i]) && count_one % 2 == 0 && count_double % 2 == 0)
			return (i);
		if (str[i] == '\'' && count_double % 2 == 0)
			count_one++;
		if (str[i] == '\"' && count_one % 2 == 0)
			count_double++;
		i++;
	}
	
	return (i - count_one - count_double);
}

int	write_words(char **res, char *str)
{
	int	i;
	int	j;
	int	count_one;
	int	count_double;

	i = 0;
	j = 0;
	count_one = 0;
	count_double = 0;
	int	len = count_space(str);
	*res = (char *)malloc((len + 1) * sizeof(char));
	*res[len] = '\0';
	printf("len: %d\n", len);


	while (i < (int)ft_strlen(str))
	{

		if (ft_separator(str[i]) && count_one % 2 == 0 && count_double % 2 == 0)
		{
			// *res[j] = str[i];
			return (i);
		}
		if (str[i] == '\'' && count_double % 2 == 0)
		{
			// i++;
			count_one++;
		}
		if (str[i] == '\"' && count_one % 2 == 0)
		{
			// i++;
			count_double++;
		}
		i++;
	// 	*res[j++] = str[i++];

	}
	return (i);
}


	// while (tmp[i])
	// {
	// 	if (tmp[i] == '$' && count_one % 2 == 0)
	// 		*str = change_dollar(tmp, i, envp_list);
	// 	if (tmp[i] == '\'' && count_double % 2 == 0)
	// 		count_one++;
	// 	if (tmp[i] == '\"' && count_one % 2 == 0)
	// 		count_double++;
	// 	i++;
	// }

char **split_by_words(char *str)
{
	char **split_by_words;
	int i;
	int words;
	int j;

	i = 0;
	j = 0;
	words = count_words(str, i, 0);
	// printf("words start: %d\n", words);
	split_by_words = (char **)malloc((words + 1) * sizeof(char *));
	if (!split_by_words)
		exit(1);
	
	printf("strlen: %d\n", (int)ft_strlen(str));
	while (i < (int)ft_strlen(str)) //while (str[i]) - проверить replace_dollar.c
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '|')
			split_by_words[j++] = ft_substr(&str[i++], 0, 1);
		else if (str[i] == '<' || str[i] == '>')
			i += write_redir(&split_by_words[j++], &str[i]);
	// 	else if (str[i + 1] && (!ft_strncmp(&str[i], "\'\'", 2) || !ft_strncmp(&str[i], "\"\"", 2)))
	// 		i += 2;
	// 	else
	// 	{
	// 		i += write_words(&split_by_words[j++], &str[i]);
	// 	}
		else
			i++;
		printf("i: %d and str: %s\n", i, &str[i]);
	}
	split_by_words[j] = NULL;
	return (split_by_words);
}

