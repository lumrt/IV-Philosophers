# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucas <lucas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 14:42:31 by lucas             #+#    #+#              #
#    Updated: 2024/10/29 17:52:52 by lucas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c parsing.c tools.c data.c wrapper.c monitoring.c simulation.c synchro.c write.c

HEADER = philosophers.h

OBJS	=	$(SRCS:%.c=%.o)

CC		=	cc #-arch arm64

CFLAGS	=	-Wall -Wextra -Werror -pthread

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o 	:	%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean	:
			@rm -f $(OBJS) $(NAME)

fclean	:	clean
			@$(RM) $(NAME)

re		:	fclean all


