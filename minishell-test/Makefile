# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marlean <marlean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 15:12:33 by marlean           #+#    #+#              #
#    Updated: 2022/06/01 17:48:37 by marlean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#НУЖНО УСТАНОВИТЬ readline ---> brew install readline
NAME_MS		=	minishell
HEADER_MS	=	minishell.h

#наша либа 
LIB_DIR	=	libft/
LIBFT	=	libft/libft.a

#подключение библиотеки readline к проекту
RL_INCLUDE	=	$(HOME)/.brew/Cellar/readline/8.1.2/include
RL_LIB		=	$(HOME)/.brew/Cellar/readline/8.1.2/lib

FILES_MS	=	main.c \
				list_utils.c \
				utils_draft.c

OBJ_MS		=	$(FILES_MS:%.c=%.o)
FLAGS_MS	=	-Wall -Wextra -Werror

.PHONY	: all clean fclean re libft

all		: libft $(NAME_MS)

libft	:
	@make -C $(LIB_DIR)

#сборка исполняемого файла с подключением библиотеки 
$(NAME_MS):	$(OBJ_MS)
	cc $(FLAGS_MS)  -lreadline -L $(RL_LIB) -I $(RL_INCLUDE) $(OBJ_MS) $(LIBFT) -o $@ 
#	cc $(FLAGS_MS) -L$(shell brew --prefix readline)/lib -lreadline $(OBJ_MS) $(LIBFT) -o $@ 

#компиляция объектных файлов
%.o	:	%.c $(LIBFT) $(HEADER_MS) Makefile
	cc $(FLAGS_MS) -c $< -o $@

clean	:
	rm -f $(OBJ_MS)
	make -C $(LIB_DIR) clean

fclean	:
	rm -f $(NAME_MS)
	MAKE -C $(LIB_DIR) fclean

re		: fclean all