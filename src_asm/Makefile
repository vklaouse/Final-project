# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschotte <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/11 11:39:28 by jschotte          #+#    #+#              #
#    Updated: 2016/06/13 10:55:42 by jschotte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRC = asm.c \
	  encode.c \
	  parsing.c \
	  tools.c \
	  get.c \
	  get2.c \
	  op.c \
	  print_file.c \
	  get3.c \
	  tools2.c \
	  tools3.c \
	  tools4.c \
	  tools6.c \
	  tools7.c \
	  error.c \
	  print_next.c \
	  tools5.c \
	  get_param.c \
	  ft_strsplit2.c \
	  print.c \
	  check.c \
	  tools8.c \

OBJ = $(addprefix $(O_DIR)/,$(SRC:.c=.o))
O_DIR = ./objs

FLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ)
	@make -C ../libft
	@echo "Making exe."
	@gcc -o $(NAME) $(FLAGS) $(OBJ) -L./ ../libft/libft.a
	@cp $(NAME) ..

$(O_DIR)/%.o: %.c
	@mkdir -p $(O_DIR)
	@gcc $(FLAGS) -o $@ -c $<

all : $(NAME)

clean:
	@echo "Removing objets."
	@rm -f $(OBJ)
	@rm -rf $(O_DIR)
	@echo "Clean done."

fclean: clean
	@echo "Removing exe."
	@rm -f $(NAME)
	@rm -f ../$(NAME)
	@echo "Fclean done."

re: fclean all

.PHONY: all fclean clean re
