# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschotte <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/09 09:40:01 by jschotte          #+#    #+#              #
#    Updated: 2016/05/31 16:28:14 by jschotte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all :
	@make -C src_asm
	@make -C src_corewar

asm:
	@make -C src_asm

corewar:
	@make -C src_corewar

clean:
	@make -C libft clean
	@make -C src_asm clean
	@make -C src_corewar clean

fclean:
	@make -C libft fclean
	@make -C src_asm fclean
	@make -C src_corewar fclean

re: 
	@make -C src_asm re
	@make -C src_corewar re

.PHONY: all fclean clean re
