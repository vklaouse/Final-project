/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instr_st.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 18:08:52 by semartin          #+#    #+#             */
/*   Updated: 2016/05/27 18:08:53 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_init : Initialise : code --> Defined on 8 bit
**						tell the instruction what kind of instr will be read
**						   size --> Size to read on the map
**						   instr --> Every byte read for this instr
**	---------------------------------------------------------------------------
**	st_show_op : If option -op : Add the operation to the buffer
**					that will be printed on screen
**	---------------------------------------------------------------------------
**	ft_proc_st : If 2nd param is a reg : Put 1st param value in it
**					Otherwise right the 1st param value on the map at :
**					PC + (Param 2 value % IDX_MOD)
**				In both case : Execute on 5 Cycles
*/

static int	ft_init_st(t_glob *g, t_proc *p)
{
	int i;

	p->instr[1] = g->arena[(p->pc + 1) % MEM_SIZE];
	ft_encode(p->instr[1], p);
	p->size = p->code[0] + p->code[1];
	i = 1;
	while (++i <= p->size + 1)
		p->instr[i] = g->arena[(p->pc + i) % MEM_SIZE];
	if (!(p->code[1] == 2 || p->code[1] == 1) || p->code[0] != 1)
	{
		p->wait = -1;
		if (g->param->s_pc)
			ft_print_pc(g, p, (2 + p->code[0] + p->code[1]));
		p->pc += (2 + p->code[0] + p->code[1]);
		clear_byte(p->instr);
		return (0);
	}
	return (1);
}

static void	st_show_op(t_glob *g, t_proc *p)
{
	int		i;
	int		nb;
	char	*s;
	char	*tmp;

	if (g->param->s_op)
	{
		if (!(s = malloc(sizeof(*s) * 64)))
			ft_error("Allocation Error : Insufficient memory");
		tmp = s;
		i = 0;
		nb = number_digit(p->number);
		ft_strcpy(tmp++, "P");
		while (i++ < 5 - nb)
			ft_strcpy(tmp++, " ");
		ft_itoa_cpy(p->number, (tmp = tmp + ft_strlen(tmp)));
		ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | st r");
		ft_itoa_cpy(p->instr[2], (tmp = tmp + 7));
		ft_strcpy((tmp = tmp + ft_strlen(tmp)), " ");
		ft_itoa_cpy(byte_into_short(&(p->instr[3])), ++tmp);
		ft_strcpy((tmp = tmp + ft_strlen(tmp)), "\n");
		ft_buffer_screen(s, 0);
		free(s);
	}
}

void		ft_proc_st(t_proc *p, t_glob *g)
{
	if (p->wait == -1)
		p->wait = 2;
	else if (p->wait > 0)
		p->wait -= 1;
	else
	{
		if (!ft_init_st(g, p))
			return ;
		if (p->size == 2 && (p->instr[2] >= 1 && p->instr[2] <= 16)
				&& (p->instr[3] >= 1 && p->instr[3] <= 16))
		{
			p->r[p->instr[3] - 1] = p->r[p->instr[2] - 1];
			st_show_op(g, p);
		}
		else if (p->size == 3 && p->instr[2] >= 1 && p->instr[2] <= 16)
		{
			ft_st(p->r[p->instr[2] - 1], byte_into_short(&(p->instr[3])), p, g);
			st_show_op(g, p);
		}
		if (g->param->s_pc)
			ft_print_pc(g, p, (2 + p->code[0] + p->code[1]));
		clear_byte(p->instr);
		p->wait = -1;
		p->pc += (2 + p->code[0] + p->code[1]);
	}
}
