# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 11:32:08 by mbatteux          #+#    #+#              #
#    Updated: 2023/07/17 11:32:10 by mbatteux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CCC = philo.c\
	utils.c

OOO = $(CCC:.c=.o)

FLAG = -Wall -Wextra -Werror

LIBINCLUDE = -lpthread -g3

all: $(NAME)

$(NAME): $(OOO)
	gcc $(OOO) $(FLAG) $(LIBINCLUDE) -o $(NAME) -g3
.c.o:
	gcc $(FLAG) $(LIBINCLUDE)  -c $< -o ${<:.c=.o} -g3
clean:
	rm -f $(OOO)
fclean: clean
	rm -f $(NAME)
re: fclean all
