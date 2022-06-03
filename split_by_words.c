/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:54:09 by marlean           #+#    #+#             */
/*   Updated: 2022/06/03 20:31:09 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*in_quotes(char *str, int quote_flag)
{
	int		len;
	char	*res = NULL;
	// printf("str: %s\n", str);
	len = 0;
	if (quote_flag == 1)
	{
		while (str[len] && str[len] != '\'')
			len++;
	}
	else if (quote_flag == 2)
	{
		while (str[len] && str[len] != '\"')
			len++;
	}
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		exit(1);
	ft_strlcpy(res, str, len + 1);
	printf("res: %s and len: %d\n", res, len);
	return (res);
}

char	**split_by_words(char	*str)
{
	char	**split_by_words;
	int		i;
	int		words;
	int		j;

	i = 0;
	j = 0;
	words = count_words(str, i, 0);
	// printf("words: %d\n", words);
	split_by_words = (char **)malloc((words + 1) * sizeof(char *));
	if (!split_by_words)
		exit(1);
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '\'')
		{

			split_by_words[j] = in_quotes(&str[i + 1], SIN_Q);
		}
		else if (str[i] == '\"')
			in_quotes(&str[i + 1], DOUB_Q);
		// printf("aft: %s\n", &str[i]);
		i++;
	}
	printf("my arr: %s\n", split_by_words[0]);
	split_by_words[words + 1] = NULL;
	// print_array(split_by_words);
	return (split_by_words);
}


void	print_array(char **arr)
{
	int	i = 0;
	// while(arr[i] != NULL)
		printf("%s\n", arr[i]);

}

//"cat lol.c | cat > lol.c"
//delimeter
//delimeters (spaces, |, >, <)