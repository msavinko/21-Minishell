#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_envp *envp_list;
	t_com *com;
	char *read_str;
	char **split_words;

	envp_list = NULL;
	split_words = NULL;
	com = NULL;
	read_envp(env, &envp_list); // в envp_list записаны переменные окружения в односвязном списке
	// read_commands(&com);		//создан односвязный список из 3 листов (3 команды), изменять вручную
	signal_handler(); //обработка сигналов

	while (1)
	{
		read_str = read_the_line();
		if (ft_strlen(read_str) > 0)
		{
			add_history(read_str);
			check_syntax(&read_str);
		}
		replace_dollar(&read_str, envp_list);
		// printf("STR %s\n\n", read_str);
		split_words = split_by_words(read_str); //Разбиваем строку на отдельные слова и спец символы

		print_array(split_words);
		// com = make_struct(split_words); // логические разледители.
	}
	rl_clear_history();
	return (0);
}

void print_array(char **arr)
{
	int i = 0;
	while (arr[i] != NULL)
	{
		printf("string %d: %s\n", i, arr[i]);
		i++;
	}
}
//Разбиваем строку на отдельные слова
//(спец символы |><, все внутри кавычек,
//символы отделенные разными пробелами).
//Сохранять в массив строк (кавычки удаляем)