# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 18:14:46 by snovaes           #+#    #+#              #
#    Updated: 2022/03/18 10:56:26 by snovaes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g

RM = rm
RMFLAGS = -rf

I_DIR = include
SRC_DIR = src
OBJ_DIR = obj

SRC_CODE =	main.c \
			util.c \
			init.c \
			monitor.c \
			philo.c \

# ============================================================================ #
#                                   COLOR                                      #
# ============================================================================ #

CL_BOLD	 = \e[1m
CL_DIM	= \e[2m
CL_UDLINE = \e[4m

NO_COLOR = \e[0m

BG_TEXT = \e[48;2;45;55;72m
BG_BLACK = \e[48;2;30;31;33m

FG_WHITE = $(NO_COLOR)\e[0;37m
FG_TEXT = $(NO_COLOR)\e[38;2;189;147;249m
FG_TEXT_PRIMARY = $(NO_COLOR)$(CL_BOLD)\e[38;2;255;121;198m

LF = \e[1K\r$(NO_COLOR)
CRLF= \n$(LF)

# ============================================================================ #

SRC = $(addprefix $(SRC_DIR)/,$(SRC_CODE))
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC_CODE:.c=.o))

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I $(I_DIR) -o $(NAME)
	@printf "$(LF)🎉 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@!$(FG_TEXT)\n$(NO_COLOR)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)

clean:
	$(RM) $(RMFLAGS) $(OBJ_DIR)
	@printf "$(LF)🧹 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)'s Object files...\n"

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)
	@printf "$(LF)🧹 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)\n$(NO_COLOR)"

re: fclean all