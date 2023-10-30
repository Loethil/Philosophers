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
	utils.c\
	minilibft.c\
	data_set.c

OOO = $(CCC:.c=.o)

FLAG = -Wall -Wextra -Werror

LIBINCLUDE = -lpthread

all: $(NAME)

$(NAME): $(OOO)
	cc $(OOO) $(FLAG) $(LIBINCLUDE) -o $(NAME)
.c.o:
	cc $(FLAG) -c $< -o ${<:.c=.o}
clean:
	rm -f $(OOO)
fclean: clean
	rm -f $(NAME)
re: fclean all
