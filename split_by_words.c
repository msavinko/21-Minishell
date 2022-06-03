/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:54:09 by marlean           #+#    #+#             */
/*   Updated: 2022/06/03 19:09:57 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_quotes(char *str, int quote_flag, char *res)
{
	int		len;

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
	printf("len: %d\n", len);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		exit(1);
	ft_strlcpy(res, str, len + 1);
	printf("res: %s and len: %d\n", res, len);
	return (len + 1);
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
	split_by_words = (char **)malloc((words + 1) * sizeof(char *));
	if (!split_by_words)
		exit(1);
	split_by_words[words] = NULL;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '\'')
			i += in_quotes(&str[i + 1], SIN_Q, split_by_words[j]);
		else if (str[i] == '\"')
			i += in_quotes(&str[i + 1], DOUB_Q, split_by_words[j]);
	// 	else
	// 		printf("no quotes\n");
	// 	printf("%s\n", split_by_words[words]);
		i++;
		// printf("arr: %s\n", split_by_words[0]);
	}


	return (split_by_words);
}




//"cat lol.c | cat > lol.c"
//delimeter
//delimeters (spaces, |, >, <)