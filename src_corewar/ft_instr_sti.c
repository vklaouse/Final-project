/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instr_sti.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 19:04:25 by semartin          #+#    #+#             */
/*   Updated: 2016/05/19 19:04:25 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_init : Initialise : code --> Defined on 8 bit
**						tell the instruction what kind of instr will be read
**						   size --> Size to read on the map
**						   instr --> Every byte read for this instr
** 	---------------------------------------------------------------------------
**	ft_sti_ind_dir : Call sti for p1 = Indirect and p2 = Direct
**	---------------------------------------------------------------------------
**	proc_sti : Add the two first param, use the result as an adress
**				put the content of the register at this adress
**				params can be : Register, Dir or Ind
**				The buffer size depend on it
**				Wait 25 cycle to execute
**				On this instr Direct are encoded on TWO byte and not 4
*/

static int	ft_init_sti(t_glob *g, t_proc *p)
{
	int i;
	int nb;

	p->instr[1] = g->arena[(p->pc + 1) % MEM_SIZE];
	ft_encode(p->instr[1], p);
	p->size = p->code[0] + p->code[1] + p->code[2];
	i = 1;
	while (++i <= p->size + 1)
		p->instr[i] = g->arena[(p->pc + i) % MEM_SIZE];
	if ((p->code[2] == 0 || p->code[2] == 2
			|| p->code[1] == 0 || p->code[0] != 1))
	{
		p->wait = -1;
		nb = (2 + p->code[0] + p->code[1] + p->code[2]);
		i = 0;
		while (i < 3)
			nb -= (p->code[i++] == 4) ? 2 : 0;
		if (g->param->s_pc)
			ft_print_pc(g, p, nb);
		p->pc += nb;
		clear_byte(p->instr);
		return (0);
	}
	return (1);
}

static void	ft_sti_ind_dir(t_glob *g, t_proc *p)
{
	int cmp;

	if (p->instr[2] >= 1 && p->instr[2] <= 16)
	{
		cmp = p->pc + (byte_into_short(&(p->instr[3])) % IDX_MOD);
		if (cmp < 0)
			cmp = MEM_SIZE + cmp;
		ft_sti(p->r[p->instr[2] - 1], byte_into_int(&g->arena[cmp])
				+ byte_into_short(&(p->instr[5])), g, p);
		flag_sti(g, p, g->arena[cmp], byte_into_short(&(p->instr[5])));
	}
	p->wait = -1;
	if (g->param->s_pc)
		ft_print_pc(g, p, 7);
	p->pc += 7;
	clear_byte(p->instr);
}

void		ft_proc_sti(t_proc *p, t_glob *g)
{
	if (p->wait == -1)
		p->wait = 22;
	else if (p->wait > 0)
		p->wait -= 1;
	else
	{
		if (!ft_init_sti(g, p))
			return ;
		if (p->code[0] == 1 && p->code[1] == 1 && p->code[2] == 1)
			ft_sti_reg_reg(g, p);
		else if (p->code[0] == 1 && p->code[1] == 4 && p->code[2] == 1)
			ft_sti_dir_reg(g, p);
		else if (p->code[0] == 1 && p->code[1] == 2 && p->code[2] == 1)
			ft_sti_ind_reg(g, p);
		else if (p->code[0] == 1 && p->code[1] == 1 && p->code[2] == 4)
			ft_sti_reg_dir(g, p);
		else if (p->code[0] == 1 && p->code[1] == 4 && p->code[2] == 4)
			ft_sti_dir_dir(g, p);
		else if (p->code[0] == 1 && p->code[1] == 2 && p->code[2] == 4)
			ft_sti_ind_dir(g, p);
	}
}
