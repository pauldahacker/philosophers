# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/24 14:40:24 by pde-masc          #+#    #+#              #
#    Updated: 2024/07/24 14:41:26 by pde-masc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -g -pthread -Wall -Wextra -Werror

HEADER = philo.h

OBJS_DIR = objs/

SRCS = main.c actions.c table.c thread_utils.c thread.c
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

BROWN =	\033[38;2;184;143;29m
ORANGE = \033[38;5;209m
BLUE = \033[0;94m
DEF_COLOR =	\033[0;39m
GREEN =	\033[0;92m

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)$(NAME) compiled succesfully!$(DEF_COLOR)"

$(OBJS_DIR)%.o:	%.c $(HEADER) Makefile
		@echo "$(BROWN)Compiling   ${BLUE}→   $(ORANGE)$< $(DEF_COLOR)"
		@$(CC) -c $(CFLAGS) $< -o $@

$(OBJS_DIR):
	@mkdir $@

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(BROWN)Successfully removed objects!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BROWN)Successfully removed binaries!$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re
