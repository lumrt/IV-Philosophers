# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucas <lucas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 14:42:31 by lucas             #+#    #+#              #
#    Updated: 2024/11/25 18:50:55 by lucas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     =		philo

SRC	     =		src/data.c	\
				src/getset.c 	\
				src/monitoring.c 	\
				src/main.c  		\
				src/parsing.c 	\
				src/simulation.c 			\
			    src/synchro.c	\
				src/tools.c 		\
				src/wrapper.c 	\
				src/write.c 	\


CC       =	    cc

C est du pur racisme juste il a vu les cheveux bouclés et il a dit non

CFLAGS   =	    -Wall -Wextra -Werror -pthread -g3 -I./inc

OBJ_DIR	 =	    obj/

SRCS     =      $(SRC)

OBJ 	 =      $(patsubst src/%.c, $(OBJ_DIR)%.o, $(SRCS))

MAKE_DIR =      mkdir -p

SMAKE	 =      make --no-print-directory

all:	        $(NAME)

$(NAME):        $(OBJ)
				@$(CC) $(CFLAGS) $(OBJ) -o $@ -pthread
				
$(OBJ_DIR)%.o:  src/%.c
			    @mkdir -p $(OBJ_DIR)
			    @$(CC) $(CFLAGS) -c $< -o $@ 

clean:
				@rm -rf $(OBJ_DIR)
				@echo "\033[1;31m======== philo object files removed ========\033[0m"

fclean:         clean
				@$(RM) $(NAME)
				@echo "\033[1;31m======= philo executable removed =======\033[0m"

re:             fclean
				@$(SMAKE)

.PHONY: clean fclean all re
