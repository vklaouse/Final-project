/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instr_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 15:07:40 by semartin          #+#    #+#             */
/*   Updated: 2016/05/19 15:07:41 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_add : Add r1 and r2 put the result into r3
**	---------------------------------------------------------------------------
**	ft_sub : Sub r1 from r2 put the result into r3
**	---------------------------------------------------------------------------
**	ft_init : Initialise : code --> Defined on 8 bit
**						tell the instruction what kind of instr will be read
**						   size --> Size to read on the map
**						   instr --> Every byte read for this instr
**	---------------------------------------------------------------------------
**	ft_op_done : Do the opration and check flag
**	---------------------------------------------------------------------------
** 	proc_op : op r1 and r2 and put the value into r3
**					if rx isn't valid, change the carry to 0
**					if the result isn't 0, chance the carry to 0
**					Wait 10 (on sub/add) cycle to execute
*/

static void	ft_add(t_proc *p)
{
	p->r[p->instr[4] - 1] = p->r[p->instr[2] - 1] + p->r[p->instr[3] - 1];
	if (p->r[p->instr[4] - 1] == 0)
		p->carry = 0;
	else
		p->carry = 1;
}

static void	ft_sub(t_proc *p)
{
	p->r[p->instr[4] - 1] = p->r[p->instr[2] - 1] - p->r[p->instr[3] - 1];
	if (p->r[p->instr[4] - 1] == 0)
		p->carry = 0;
	else
		p->carry = 1;
}

static int	ft_init_op(t_glob *g, t_proc *p)
{
	int i;

	p->instr[1] = g->arena[(p->pc + 1) % MEM_SIZE];
	ft_encode(p->instr[1], p);
	p->size = p->code[0] + p->code[1] + p->code[2];
	i = 1;
	while (++i <= p->size + 1)
		p->instr[i] = g->arena[(p->pc + i) % MEM_SIZE];
	if (p->code[2] != 1 || p->code[1] != 1 || p->code[0] != 1)
	{
		p->wait = -1;
		if (g->param->s_pc)
			ft_print_pc(g, p, 2 + p->code[0] + p->code[1] + p->code[2]);
		p->pc += (2 + p->code[0] + p->code[1] + p->code[2]);
		clear_byte(p->instr);
		return (0);
	}
	return (1);
}

static void	ft_op_done(t_glob *g, t_proc *p, int n)
{
	if (n == 0)
	{
		ft_add(p);
		if (g->param->s_op)
			ft_print_add(p);
	}
	if (n == 1)
	{
		ft_sub(p);
		if (g->param->s_op)
			ft_print_sub(p);
	}
}

void		ft_proc_op(t_proc *p, t_glob *g, int n)
{
	if (p->wait == -1)
		p->wait = 7;
	else if (p->wait > 0)
		p->wait -= 1;
	else
	{
		if (!ft_init_op(g, p))
			return ;
		if (p->size == 3)
		{
			if (!((p->instr[2] < 1 || p->instr[2] > 16)
					|| ((p->instr[3] < 1 || p->instr[3] > 16))
					|| ((p->instr[4] < 1 || p->instr[4] > 16))))
				ft_op_done(g, p, n);
			if (g->param->s_pc)
				ft_print_pc(g, p, 2 + p->code[0] + p->code[1] + p->code[2]);
			p->pc += (2 + p->code[0] + p->code[1] + p->code[2]);
			clear_byte(p->instr);
			p->wait = -1;
		}
	}
}
