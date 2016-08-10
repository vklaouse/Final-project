/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instr_bit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 15:00:34 by semartin          #+#    #+#             */
/*   Updated: 2016/06/13 15:00:35 by semartin         ###   ########.fr       */
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
**	ft_get_value_p1 : Get the value of the first param
**	---------------------------------------------------------------------------
**	ft_get_value_p2 : Get the value of the second param
**	---------------------------------------------------------------------------
**	ft_bit : Do the bit operation with p1 and p2
**	---------------------------------------------------------------------------
**	proc_bit : Call bit op between p1 and p2 and put the value into r3
**				if r3 == 0 --> carry == 1, else carry == 0
**				Wait 6 cycle to execute
*/

static int	ft_init_bit(t_glob *g, t_proc *p)
{
	int i;

	p->instr[1] = g->arena[(p->pc + 1) % MEM_SIZE];
	ft_encode(p->instr[1], p);
	p->size = p->code[0] + p->code[1] + p->code[2];
	i = 1;
	while (++i <= p->size + 1)
		p->instr[i] = g->arena[(p->pc + i) % MEM_SIZE];
	if (p->code[2] != 1 || p->code[1] == 0 || p->code[0] == 0)
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

static int	ft_get_value_p1(t_proc *p, t_glob *g, int *p1)
{
	int cmp;

	if (p->code[0] == 1 && p->instr[2] >= 1 && p->instr[2] <= 16)
		*p1 = p->r[p->instr[2] - 1];
	else if (p->code[0] == 2)
	{
		cmp = p->pc + (byte_into_short(&(p->instr[2])) % IDX_MOD);
		if (cmp < 0)
			cmp = MEM_SIZE + cmp;
		*p1 = byte_into_int(&g->arena[cmp]);
	}
	else if (p->code[0] == 4)
		*p1 = byte_into_int(&(p->instr[2]));
	else
		return (0);
	return (1);
}

static int	ft_get_value_p2(t_proc *p, t_glob *g, int *p2)
{
	int cmp;

	if (p->code[1] == 1 && p->instr[2 + p->code[0]] >= 1
			&& p->instr[2 + p->code[0]] <= 16)
		*p2 = p->r[p->instr[2 + p->code[0]] - 1];
	else if (p->code[1] == 2)
	{
		cmp = p->pc + (byte_into_short(&(p->instr[2 + p->code[0]]))
				% IDX_MOD);
		if (cmp < 0)
			cmp = MEM_SIZE + cmp;
		*p2 = byte_into_int(&g->arena[cmp]);
	}
	else if (p->code[1] == 4)
		*p2 = byte_into_int(&(p->instr[2 + p->code[0]]));
	else
		return (0);
	if (p->instr[2 + p->code[0] + p->code[1]] < 1
			|| p->instr[2 + p->code[0] + p->code[1]] > 16)
		return (0);
	return (1);
}

static void	ft_bit(t_glob *g, t_proc *p, int n)
{
	int p1;
	int p2;

	if (!(ft_get_value_p1(p, g, &p1) && ft_get_value_p2(p, g, &p2)))
		return ;
	if (n == 0)
	{
		p->r[p->instr[2 + p->code[0] + p->code[1]] - 1] = p1 & p2;
		if (g->param->s_op)
			ft_print_and(p, p1, p2);
	}
	else if (n == 1)
	{
		p->r[p->instr[2 + p->code[0] + p->code[1]] - 1] = p1 | p2;
		if (g->param->s_op)
			ft_print_or(p, p1, p2);
	}
	else if (n == 2)
	{
		p->r[p->instr[2 + p->code[0] + p->code[1]] - 1] = p1 ^ p2;
		if (g->param->s_op)
			ft_print_xor(p, p1, p2);
	}
	p->carry = p->r[p->instr[2 + p->code[0] + p->code[1]] - 1] ? 1 : 0;
}

void		ft_proc_bit(t_proc *p, t_glob *g, int n)
{
	if (p->wait == -1)
		p->wait = 3;
	else if (p->wait > 0)
		p->wait -= 1;
	else
	{
		if (!ft_init_bit(g, p))
			return ;
		ft_bit(g, p, n);
		if (g->param->s_pc)
			ft_print_pc(g, p, 2 + p->code[0] + p->code[1] + p->code[2]);
		p->pc += (2 + p->code[0] + p->code[1] + p->code[2]);
		clear_byte(p->instr);
		p->wait = -1;
	}
}
