# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschotte <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/11 11:39:28 by jschotte          #+#    #+#              #
#    Updated: 2016/05/25 17:54:34 by vklaouse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC = corewar.c \
		ft_aff_bit_op.c \
		ft_algo.c \
		ft_core.c \
		ft_cycle.c \
		ft_dump.c \
		ft_error.c \
		ft_flag.c \
		ft_fnct.c \
		ft_fnct2.c \
		ft_init.c \
		ft_instr_aff.c \
		ft_instr_bit.c \
		ft_instr_op.c \
		ft_instr_fork.c \
		ft_instr_ld.c \
		ft_instr_ldi.c \
		ft_instr_live.c \
		ft_instr_st.c \
		ft_instr_sti.c \
		ft_instr_zjmp.c \
		ft_ldi.c \
		ft_ldi_reg.c \
		ft_map.c \
		ft_onscreen.c \
		ft_parsing.c \
		ft_pixel_put_to_image.c \
		ft_print_screen.c \
		ft_st.c \
		ft_sti.c \
		ft_sti_reg.c \
		visualisateur.c \
		visualisateur2.c \
		visualisateur3.c \
		modif_visu.c \
		visu_processus.c

OBJ = $(addprefix $(O_DIR)/,$(SRC:.c=.o))
O_DIR = ./objs

FLAGS = -Wall -Wextra -Werror
MLX_FLAG = -L./minilibx -lmlx -L/usr/X11/lib -lXext -lX11

$(NAME): $(OBJ)
	@make -C ../libft/
	@echo "Making exe."
	@gcc -o $(NAME) $(FLAGS) $(MLX_FLAG)  $(OBJ) -L./ ../libft/libft.a
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
