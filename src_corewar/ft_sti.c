/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 14:29:13 by semartin          #+#    #+#             */
/*   Updated: 2016/05/09 14:29:13 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_change_arena : Change the arena and the visualistaeur if -v
**	---------------------------------------------------------------------------
**	sti_show_op : 2nd part of ft_flag_sti
**	---------------------------------------------------------------------------
**	ft_flag_sti : If option -op : Add the operation to the buffer
**					that will be printed on screen
**	---------------------------------------------------------------------------
** 	ft_sti : Sum x and y. Use it as an adress. Put r value at this adress
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

static void	sti_show_op(t_proc *p, int n1, int n2, char *tmp)
{
	ft_itoa_cpy(p->number, tmp);
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | sti r");
	ft_itoa_cpy(p->instr[2], (tmp += 8));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " ");
	ft_itoa_cpy(n1, ++tmp);
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " ");
	ft_itoa_cpy(n2, ++tmp);
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), "\n       | -> store to ");
	ft_itoa_cpy(n1, (tmp += 22));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " + ");
	ft_itoa_cpy(n2, (tmp += 3));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " = ");
	ft_itoa_cpy(n1 + n2, (tmp += 3));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " (with pc and mod ");
	ft_itoa_cpy(p->pc + (n1 + n2) % IDX_MOD, (tmp += 18));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), ")\n");
}

void		flag_sti(t_glob *g, t_proc *p, int n1, int n2)
{
	int		i;
	int		nb;
	char	*s;
	char	*tmp;

	if (g->param->s_op)
	{
		if (!(s = malloc(sizeof(*s) * 128)))
			ft_error("Allocation Error : Insufficient memory");
		tmp = s;
		i = 0;
		nb = number_digit(p->number);
		ft_strcpy(tmp++, "P");
		while (i++ < 5 - nb)
			ft_strcpy(tmp++, " ");
		sti_show_op(p, n1, n2, tmp);
		ft_buffer_screen(s, 0);
		free(s);
	}
}

void		ft_sti(int r, int nb, t_glob *g, t_proc *p)
{
	int cmp;

	cmp = p->pc + (nb % IDX_MOD);
	if (cmp >= 0)
		ft_change_arena(g, p, cmp, r);
	else
		ft_change_arena(g, p, MEM_SIZE + cmp, r);
}
