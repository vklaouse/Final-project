#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: semartin <semartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/05 14:06:48 by semartin          #+#    #+#              #
#    Updated: 2016/05/11 15:11:35 by semartin         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a
SRC_DIR	= ./srcs/
SRC = ft_atoi.c ft_isprint.c ft_memset.c ft_strlcat.c \
		ft_strrchr.c ft_bzero.c ft_memccpy.c ft_strcat.c \
		ft_strlen.c ft_strstr.c ft_isalnum.c ft_memchr.c \
		ft_strchr.c ft_strncat.c ft_tolower.c ft_isalpha.c \
		ft_memcmp.c ft_strcmp.c ft_strncmp.c ft_toupper.c \
		ft_isascii.c ft_memcpy.c ft_strcpy.c ft_strncpy.c \
		ft_isdigit.c ft_memmove.c ft_strdup.c ft_strnstr.c \
		ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c \
		ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
		ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
		ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c \
		ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_lstadd.c ft_lstdelone.c ft_lstnew.c \
        ft_lstdel.c ft_lstiter.c ft_lstmap.c ft_strnjoin.c \
		ft_abs.c ft_sqrt.c ft_power.c ft_free_tabstr.c \
		ft_strjoin_free.c ft_lstpushback.c ft_round.c \
		ft_strndup.c ft_power_float.c ft_strnjoin_free.c \
		get_next_line.c ft_atol.c ft_itoa_base.c
VPATH	= $(SRC_DIR)
OBJ = $(addprefix $(O_DIR)/,$(SRC:.c=.o))
O_DIR = ./obj

$(NAME): $(OBJ)
	@echo "Creating library."
	@ar rc $(NAME) $(OBJ)
	@echo "Creating table of content"
	@ranlib $(NAME)

$(O_DIR)/%.o: %.c
	@mkdir -p $(O_DIR)
	@gcc -Wall -Werror -Wextra -I includes -o $@ -c $<

all: $(NAME) 

clean:
	@echo "Removing objets."
	@rm -f $(OBJ)
	@rm -rf $(O_DIR)
	@echo "Clean done."

fclean: clean
	@echo "Removing library."
	@rm -f $(NAME)
	@echo "Fclean done."

re: fclean all

.PHONY : all clean fclean re
