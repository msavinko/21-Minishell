#include "minishell.h"

t_split	*init_split(char *str)
{
	t_split	*split_w;

	split_w = malloc(sizeof(t_split));
	str = ft_strtrim(str, WHITE_SPACES);
	split_w->words = count_words(str, 0, 0);
	split_w->split_by_words = (char **)malloc((split_w->words + 1)
			* sizeof(char *));
	if (!split_w->split_by_words)
		exit(1);
	return (split_w);
}

t_words	*init_write_w(char *str)
{
	t_words	*write_w;

	write_w = malloc(sizeof(t_words));
	write_w->count_one = 0;
	write_w->count_double = 0;
	write_w->j = 0;
	write_w->i = 0;
	write_w->len = count_space(str);
	write_w->res = malloc(sizeof(char *) * write_w->len + 1);
	if (!write_w->res)
		exit(1);
	return (write_w);
}
