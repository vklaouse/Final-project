/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi_reg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 19:22:06 by semartin          #+#    #+#             */
/*   Updated: 2016/05/27 19:22:11 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_ldi_reg_reg : Call ldi/lldi for p1 = Register and p2 = Register
**	---------------------------------------------------------------------------
**	ft_ldi_dir_reg : Call ldi/lldi for p1 = Direct and p2 = Register
**	---------------------------------------------------------------------------
**	ft_ldi_ind_reg : Call ldi/lldi for p1 = Indirect and p2 = Register
**	---------------------------------------------------------------------------
**	ft_ldi_reg_dir : Call ldi/lldi for p1 = Register and p2 = Direct
**	---------------------------------------------------------------------------
**	ft_ldi_dir_dir : Call ldi/lldi for p1 = Direct and p2 = Direct
*/

void	ft_ldi_reg_reg(t_glob *g, t_proc *p, int n)
{
	t_ldi	var;

	if ((p->instr[2] >= 1 && p->instr[2] <= 16)
		&& ((p->instr[3] >= 1 && p->instr[3] <= 16))
		&& ((p->instr[4] >= 1 && p->instr[4] <= 16)))
	{
		var.n1 = p->r[p->instr[2] - 1];
		var.n2 = p->r[p->instr[3] - 1];
		var.r = p->instr[4];
		ft_core_ldi(g, p, n, var);
	}
	p->wait = -1;
	if (g->param->s_pc)
		ft_print_pc(g, p, 5);
	p->pc += 5;
	clear_byte(p->instr);
}

void	ft_ldi_dir_reg(t_glob *g, t_proc *p, int n)
{
	t_ldi	var;

	if ((p->instr[4] >= 1 && p->instr[4] <= 16)
		&& ((p->instr[5] >= 1 && p->instr[5] <= 16)))
	{
		var.n1 = byte_into_short(&(p->instr[2]));
		var.n2 = p->r[p->instr[4] - 1];
		var.r = p->instr[5];
		ft_core_ldi(g, p, n, var);
	}
	p->wait = -1;
	if (g->param->s_pc)
		ft_print_pc(g, p, 6);
	p->pc += 6;
	clear_byte(p->instr);
}

void	ft_ldi_ind_reg(t_glob *g, t_proc *p, int n)
{
	int		cmp;
	t_ldi	var;

	if ((p->instr[4] >= 1 && p->instr[4] <= 16)
		&& ((p->instr[5] >= 1 && p->instr[5] <= 16)))
	{
		cmp = p->pc + (byte_into_short(&(p->instr[2])) % IDX_MOD);
		if (cmp < 0)
			cmp = MEM_SIZE + cmp;
		if (cmp < 0)
			cmp = MEM_SIZE + cmp;
		var.n1 = byte_into_int(&g->arena[cmp]);
		var.n2 = p->r[p->instr[4] - 1];
		var.r = p->instr[5];
		ft_core_ldi(g, p, n, var);
	}
	p->wait = -1;
	if (g->param->s_pc)
		ft_print_pc(g, p, 6);
	p->pc += 6;
	clear_byte(p->instr);
}

void	ft_ldi_reg_dir(t_glob *g, t_proc *p, int n)
{
	t_ldi	var;

	if ((p->instr[2] >= 1 && p->instr[2] <= 16)
		&& (p->instr[5] >= 1 && p->instr[5] <= 16))
	{
		var.n1 = p->r[p->instr[2] - 1];
		var.n2 = byte_into_short(&(p->instr[3]));
		var.r = p->instr[5];
		ft_core_ldi(g, p, n, var);
	}
	p->wait = -1;
	if (g->param->s_pc)
		ft_print_pc(g, p, 6);
	p->pc += 6;
	clear_byte(p->instr);
}

void	ft_ldi_dir_dir(t_glob *g, t_proc *p, int n)
{
	t_ldi	var;

	if ((p->instr[6] >= 1 && p->instr[6] <= 16))
	{
		var.n1 = byte_into_short(&(p->instr[2]));
		var.n2 = byte_into_short(&(p->instr[4]));
		var.r = p->instr[6];
		ft_core_ldi(g, p, n, var);
	}
	p->wait = -1;
	if (g->param->s_pc)
		ft_print_pc(g, p, 7);
	p->pc += 7;
	clear_byte(p->instr);
}
