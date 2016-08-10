/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 17:57:15 by semartin          #+#    #+#             */
/*   Updated: 2016/06/02 17:35:28 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"
#include <fcntl.h>

/*
** 	ft_init_name :  Alloc the t_prog
**	---------------------------------------------------------------------------
** 	ft_read_bytecode : Alloc and read all bytecode
**	---------------------------------------------------------------------------
** 	ft_glob_init : Alloc the g_glob struct and fill the map with 0x0
*/

static void		ft_init_name(t_glob *g)
{
	if (!(g->prog = malloc(sizeof(t_prog))))
		ft_error("Allocation Error : Insufficient memory");
}

static void		ft_read_bytecode(t_glob *g)
{
	int		i;
	int		fd;
	int		ret;
	t_byte	*tmp;

	if (!(g->bcode = malloc(sizeof(t_byte *) * (g->nb_champ + 1))))
		ft_error("Allocation Error : Insufficient memory");
	i = 0;
	while (i < g->nb_champ)
	{
		if (!(tmp = malloc(sizeof(*tmp) * MAX_SIZE + 1)))
			ft_error("Allocation Error : Insufficient memory");
		if (!(fd = open(g->name_files[i], O_RDONLY)))
			ft_error("Wrong File : Cannot be open");
		ret = read(fd, tmp, MAX_SIZE + 1);
		if (ret == MAX_SIZE + 1)
			ft_error("Champion's lenth too long : MEM_SIZE / 6 is max size");
		else
			g->bcode[g->number_champ[i] - 1] = tmp;
		tmp = NULL;
		g->champ[g->number_champ[i] - 1]->size = ret;
		close(fd);
		i++;
	}
}

t_glob			*ft_glob_init(int nb, char **str)
{
	t_glob	*g;
	int		i;

	if (!(g = malloc(sizeof(*g))))
		ft_error("Allocation Error : Insufficient memory");
	if (!(g->param = malloc(sizeof(t_param))))
		ft_error("Allocation Error : Insufficient memory");
	parse_flags(g, str, nb);
	if (!(g->arena = malloc(sizeof(t_byte) * MEM_SIZE)))
		ft_error("Allocation Error : Insufficient memory");
	if (!(g->color = malloc(sizeof(t_byte) * MEM_SIZE)))
		ft_error("Allocation Error : Insufficient memory");
	if (!(g->champ = malloc(sizeof(t_champ *) * g->nb_champ)))
		ft_error("Allocation Error : Insufficient memory");
	i = 0;
	while (i < g->nb_champ)
	{
		if (!(g->champ[i++] = malloc(sizeof(t_champ))))
			ft_error("Allocation Error : Insufficient memory");
	}
	ft_init_name(g);
	ft_champ_right(g);
	ft_champ_order(g);
	ft_read_bytecode(g);
	return (g);
}
