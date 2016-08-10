/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file..c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 13:36:16 by jschotte          #+#    #+#             */
/*   Updated: 2016/06/09 14:18:05 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"

void	print_str(char *str, int size, int fd)
{
	char *tmp;

	tmp = ft_strnew(size);
	ft_strcat(tmp, str);
	write(fd, tmp, size);
}

void	print_magic(int pfd)
{
	char	nb_magic[4];

	nb_magic[0] = (COREWAR_EXEC_MAGIC & 0xFFFFFFFF) >> 24;
	nb_magic[1] = (COREWAR_EXEC_MAGIC & 0xFFFFFF) >> 16;
	nb_magic[2] = (COREWAR_EXEC_MAGIC & 0xFFFF) >> 8;
	nb_magic[3] = (COREWAR_EXEC_MAGIC & 0xFF);
	write(pfd, nb_magic, sizeof(COREWAR_EXEC_MAGIC));
}

int		print_int(long nb, int pfd)
{
	char	nb_magic[2];

	nb_magic[0] = (nb & 0xFFFF) >> 8;
	nb_magic[1] = (nb & 0xFF);
	write(pfd, nb_magic, sizeof(nb_magic));
	return (2);
}

int		print_adressnum(long nb, int pfd)
{
	char	nb_magic[4];

	nb_magic[0] = (nb & 0xFFFFFFFF) >> 24;
	nb_magic[1] = (nb & 0xFFFFFF) >> 16;
	nb_magic[2] = (nb & 0xFFFF) >> 8;
	nb_magic[3] = (nb & 0xFF);
	write(pfd, nb_magic, sizeof(nb_magic));
	return (4);
}

void	print_size(t_inst *inst, int pfd)
{
	char	nb_magic[8];
	int		nb;

	nb = 0;
	while (inst != NULL)
	{
		nb = inst->par_sum_t_h;
		inst = inst->next;
	}
	nb_magic[0] = (nb & 0xFFFFFFFFFFFFFFFF) >> 56;
	nb_magic[1] = (nb & 0xFFFFFFFFFFFFFF) >> 48;
	nb_magic[2] = (nb & 0xFFFFFFFFFFFF) >> 40;
	nb_magic[3] = (nb & 0xFFFFFFFFFF) >> 32;
	nb_magic[4] = (nb & 0xFFFFFFFF) >> 24;
	nb_magic[5] = (nb & 0xFFFFFF) >> 16;
	nb_magic[6] = (nb & 0xFFFF) >> 8;
	nb_magic[7] = (nb & 0xFF);
	write(pfd, nb_magic, sizeof(nb_magic));
}
