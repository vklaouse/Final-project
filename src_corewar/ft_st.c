/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 13:35:48 by semartin          #+#    #+#             */
/*   Updated: 2016/05/09 13:35:52 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
** 	ft_st : Put the value of r1 in the right adress
** 	The address will be (pc + r2) % IDX_MOD
** 	% IDX_MOD is here to not go out of the memory
**	The memory is a circle
*/

static void	ft_change_arena(t_glob *g, t_proc *p, int cmp, int r)
{
	g->arena[(cmp + 3) % MEM_SIZE] = r % 256;
	g->arena[(cmp + 2) % MEM_SIZE] = ((unsigned int)r / 256) % 256;
	g->arena[(cmp + 1) % MEM_SIZE] = ((unsigned int)r / 65536) % 256;
	g->arena[(cmp) % MEM_SIZE] = ((unsigned int)r / 16777216) % 256;
	if (g->param->v)
	{
		g->color[(cmp + 3) % MEM_SIZE] = -p->player;
		g->color[(cmp + 2) % MEM_SIZE] = -p->player;
		g->color[(cmp + 1) % MEM_SIZE] = -p->player;
		g->color[(cmp) % MEM_SIZE] = -p->player;
		modif_arena(g, cmp % MEM_SIZE);
		modif_arena(g, (cmp + 1) % MEM_SIZE);
		modif_arena(g, (cmp + 2) % MEM_SIZE);
		modif_arena(g, (cmp + 3) % MEM_SIZE);
	}
}

void		ft_st(int r, int r2, t_proc *p, t_glob *g)
{
	int cmp;

	cmp = p->pc + (r2 % IDX_MOD);
	if (cmp >= 0)
		ft_change_arena(g, p, cmp, r);
	else
		ft_change_arena(g, p, MEM_SIZE + cmp, r);
}
