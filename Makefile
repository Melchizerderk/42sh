#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/19 16:35:23 by mngomane          #+#    #+#              #
#    Updated: 2014/06/25 04:30:52 by mngomane         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = 42sh

SRC = main.c\
		bg.c\
		building.c\
		building2.c\
		catch_me.c\
		cd.c\
		dash_cd.c\
		echo.c\
		entry.c\
		error.c\
		father.c\
		father2.c\
		father3.c\
		free_job.c\
		free_list.c\
		imdumb.c\
		inhib.c\
		initial.c\
		job_control.c\
		job_operator.c\
		job_tools.c\
		list_edit.c\
		non_pipe_redir.c\
		non_pipe_redir2.c\
		pars_functions.c\
		pars_functions_redir.c\
		parser.c\
		parser2.c\
		pipe.c\
		recurs.c\
		setenv.c\
		son.c\
		string.c\
		string2.c\
		sub_init.c\
		sub_main.c\
		sub_main2.c\
		unsetenv.c

SRCDIR = srcs/

OBJDIR = bins/

OBJ = $(addprefix $(OBJDIR), $(SRC:%.c=%.o))

CC1 = /usr/bin/clang

CC2 = gcc

FLAGS1 = -Weverything -Wextra -I incs

FLAGS2 = -Werror -Wextra -Wall -I incs

.PHONY: all clean fclean re

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJ)
	@$(CC1) $(FLAGS1) -o $(NAME) $^
	$(CC2) $(FLAGS2) -o $(NAME) $^

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC1) $(FLAGS1) -c $< -o $@
	$(CC2) $(FLAGS2) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
