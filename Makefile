# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malmeida <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/28 12:04:27 by malmeida          #+#    #+#              #
#    Updated: 2021/10/28 13:23:46 by malmeida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS	+=	--quiet

			# Library Name #
NAME		=
PHILO		=	philo

			# Mandatory Variables #
SRC_PHILO	=	./srcs/*.c

			# Compiling Variables #
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
INC		= -I./includes
RM		= rm -f

			# Color Variables #
GREEN		= \e[0;32m
RED			= \e[0;31m
YELLOW		= \e[0;33m
RESET		= \e[0m

all: $(PHILO)

$(NAME): all

$(PHILO): $(SRC_PHILO)
	@ $(CC) $(CFLAG) $(SRC_PHILO) -o $(PHILO)
	@printf "[$(GREEN)SUCCESS$(RESET)] Philosophers compiled.\n"

clean:
	@ $(RM) $(PHILO)
	@printf "[$(YELLOW)SUCCESS$(RESET)] Executable removed.\n"

fclean:
	@ $(RM) $(PHILO)
	@printf "[$(YELLOW)SUCCESS$(RESET)] Executable removed.\n"

re: fclean all

mandatory:	$(PHILO)

m:	mandatory
