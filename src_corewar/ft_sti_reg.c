/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti_reg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 19:49:51 by semartin          #+#    #+#             */
/*   Updated: 2016/05/27 19:49:51 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_sti_reg_reg : Call sti for p1 = Register and p2 = Register
**	---------------------------------------------------------------------------
**	ft_sti_dir_reg : Call sti for p1 = Direct and p2 = Register
**	---------------------------------------------------------------------------
**	ft_sti_ind_reg : Call sti for p1 = Indirect and p2 = Register
**	---------------------------------------------------------------------------
**	ft_sti_reg_dir : Call sti for p1 = Register and p2 = Direct
**	---------------------------------------------------------------------------
**	ft_sti_dir_dir : Call sti for p1 = Direct and p2 = Direct
*/

void	ft_sti_reg_reg(t_glob *g, t_proc *p)
{
	if ((p->instr[2] >= 1 && p->instr[2] <= 16)
		&& ((p->instr[3] >= 1 && p->instr[3] <= 16))
		&& ((p->instr[4] >= 1 && p->instr[4] <= 16)))
	{
		ft_sti(p->r[p->instr[2] - 1], p->r[p->instr[3] - 1]
				+ p->r[p->instr[4] - 1], g, p);
		flag_sti(g, p, p->r[p->instr[3] - 1], p->r[p->instr[4] - 1]);
	}
	p->wait = -1;
	if (g->param->s_pc)
		ft_print_pc(g, p, 5);
	p->pc += 5;
	clear_byte(p->instr);
}

void	ft_sti_dir_reg(t_glob *g, t_proc *p)
{
	if ((p->instr[2] >= 1 && p->instr[2] <= 16)
		&& ((p->instr[5] >= 1 && p->instr[5] <= 16)))
	{
		ft_sti(p->r[p->instr[2] - 1], byte_into_short(&(p->instr[3]))
				+ p->r[p->instr[5] - 1], g, p);
		flag_sti(g, p, byte_into_short(&(p->instr[3])),
					p->r[p->instr[5] - 1]);
	}
	p->wait = -1;
	if (g->param->s_pc)
		ft_print_pc(g, p, 6);
	p->pc += 6;
	clear_byte(p->instr);
}

void	ft_sti_ind_reg(t_glob *g, t_proc *p)
{
	int cmp;

	if ((p->instr[2] >= 1 && p->instr[2] <= 16)
		&& ((p->instr[5] >= 1 && p->instr[5] <= 16)))
	{
		cmp = p->pc + (byte_into_short(&(p->instr[3])) % IDX_MOD);
		if (cmp < 0)
			cmp = MEM_SIZE + cmp;
		ft_sti(p->r[p->instr[2] - 1], byte_into_int(&g->arena[cmp])
				+ p->r[p->instr[5] - 1], g, p);
		flag_sti(g, p, g->arena[cmp], p->r[p->instr[5] - 1]);
	}
	p->wait = -1;
	if (g->param->s_pc)
		ft_print_pc(g, p, 6);
	p->pc += 6;
	clear_byte(p->instr);
}

void	ft_sti_reg_dir(t_glob *g, t_proc *p)
{
	if ((p->instr[2] >= 1 && p->instr[2] <= 16)
		&& ((p->instr[3] >= 1 && p->instr[3] <= 16)))
	{
		ft_sti(p->r[p->instr[2] - 1], p->r[p->instr[3] - 1]
				+ byte_into_short(&(p->instr[4])), g, p);
		flag_sti(g, p, p->r[p->instr[3] - 1],
					byte_into_short(&(p->instr[4])));
	}
	p->wait = -1;
	if (g->param->s_pc)
		ft_print_pc(g, p, 6);
	p->pc += 6;
	clear_byte(p->instr);
}

void	ft_sti_dir_dir(t_glob *g, t_proc *p)
{
	if (p->instr[2] >= 1 && p->instr[2] <= 16)
	{
		ft_sti(p->r[p->instr[2] - 1], byte_into_short(&(p->instr[3]))
				+ byte_into_short(&(p->instr[5])), g, p);
		flag_sti(g, p, byte_into_short(&(p->instr[3])),
					byte_into_short(&(p->instr[5])));
	}
	p->wait = -1;
	if (g->param->s_pc)
		ft_print_pc(g, p, 7);
	p->pc += 7;
	clear_byte(p->instr);
}
