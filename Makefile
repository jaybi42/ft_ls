#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguthert <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/30 15:25:02 by jguthert          #+#    #+#              #
#    Updated: 2016/04/01 01:57:30 by jguthert         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

##=-  Compilatator -=##

NAME = ft_ls
CC = gcc


##=-  FLAGS -=##

CFLAGS = -Wall -Wextra -g3 #-Werror


##=-  PATH -=##

OBJPATH = obj
SRCPATH = srcs
LIBFT_PATH = libft

INCLUDE_PATH = include/

##=-  Rules -=##

LIBFT = -L $(LIBFT_PATH)
LIBS = $(LIBFT) -lft

INCLUDES = -I./ -I $(LIBFT_PATH)/includes -I $(INCLUDE_PATH)


##=-  Files -=##

OBJ = $(SRC:$(SRCPATH)/%.c=$(OBJPATH)/%.o)
	SRC = $(addprefix $(SRCPATH)/,$(SRCSFILES))

SRCSFILES =             main.c			\
						get_info.c		\
						make_argv.c		\
						sort_list.c		\
						make_list.c		\
						print_ls.c		\
						print_ls_time.c	\
						print_ls_ext.c	\
						print_ls_error.c\
						x_attr.c		\

##=-  Process -=##

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[33mProcessing\n\033[0m"
	@$(MAKE) -C libft/
	@$(CC) -o $@ $(CFLAGS) $(OBJ) $(LIBS)
	@echo "\n\033[33mEnd of the Process\n\033[0m"

$(OBJ): $(OBJPATH)/%.o : $(SRCPATH)/%.c
	@mkdir -p $(dir $@)
#	@echo "\033[32m"
	@$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<
#	@echo "\033[0m"

clean:
	/bin/rm -rf $(OBJPATH)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all