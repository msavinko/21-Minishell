# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marlean <marlean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 15:12:33 by marlean           #+#    #+#              #
#    Updated: 2022/06/03 18:32:14 by marlean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#НУЖНО УСТАНОВИТЬ readline ---> brew install readline
NAME_MS		=	minishell
HEADER_MS	=	minishell.h

#наша либа 
LIB_DIR	=	libft/
LIBFT	=	libft/libft.a

#подключение библиотеки readline к проекту
# RL_INCLUDE	=	$(HOME)/.brew/Cellar/readline/8.1/include
# RL_LIB		=	$(HOME)/.brew/Cellar/readline/8.1/lib

FILES_MS	=	main.c \
				list_utils.c \
				signal_handler.c \
				utils_draft.c \
				check_syntax.c \
				split_by_words.c \
				count_words.c \


OBJ_MS		=	$(FILES_MS:%.c=%.o) 
FLAGS_MS	=	-Wall -Wextra -Werror


.PHONY	: all clean fclean re libft

all		: libft $(NAME_MS)

libft	:
	@make -C $(LIB_DIR)

#компиляция объектных файлов
%.o	:	%.c  $(HEADER_MS) Makefile
	cc $(FLAGS_MS) -I$(shell brew --prefix readline)/include -c $< -o $@ -I $(HEADER_MS)
#	cc $(FLAGS_MS) -c $< -o $@ 

#сборка исполняемого файла с подключением библиотеки 
$(NAME_MS):	$(OBJ_MS)
	cc $(FLAGS_MS) $(LIBFT) -L$(shell brew --prefix readline)/lib -lreadline $(OBJ_MS) -o $@ 
#	cc $(FLAGS_MS) -L $(RL_LIB) -I $(RL_INCLUDE) -lreadline $(OBJ_MS) $(LIBFT) -o $@ 

clean	:
	rm -rf $(OBJ_MS)
	make -C $(LIB_DIR) clean

fclean	:
	rm -rf $(NAME_MS)
	MAKE -C $(LIB_DIR) fclean

re		: fclean all

# -L/Users/ваш ник/.brew/Cellar/readline/8.1/lib/
# -I/Users/ваш ник/.brew/Cellar/readline/8.1/include