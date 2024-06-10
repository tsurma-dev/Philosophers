# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:40:37 by tsurma            #+#    #+#              #
#    Updated: 2024/06/10 20:03:50 by tsurma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRC =	src/philo.c\
		src/parser.c\
		src/thread_weaver.c\
		src/utils.c

OBJ = $(SRC:.c=.o)

CC =		cc
CFLAGS =	-Wall -Werror -Wextra -g3 -fsanitize=address
MAKEFLAGS =	--no-print-directory


all:	$(NAME)

.SILENT $(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
