/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instr_ldi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:13:25 by semartin          #+#    #+#             */
/*   Updated: 2016/05/19 17:13:25 by semartin         ###   ########.fr       */
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
**	ft_ldi_ind_dir : Call ldi/lldi for p1 = Indirect and p2 = Direct
**	---------------------------------------------------------------------------
**	ft_ldi_core : Call the ldi fnct that will do the calcul
**					Then if -op call the fnct that will print op on screen
**	---------------------------------------------------------------------------
**	proc_ldi : Add the two first param, use the result as an adress
**				read it content, put this content into the register
**				params can be : Register, Dir or Ind
**				The buffer size depend on it
**				Wait 25 cycle to execute
** 				for lldi : Ignore IDX_MOD and modify the carry
**				Wait 50 cycle to execute
**				On this instr Direct are encoded on TWO byte and not 4
*/

static int	ft_init_ldi(t_glob *g, t_proc *p)
{
	int	i;
	int nb;

	p->instr[1] = g->arena[(p->pc + 1) % MEM_SIZE];
	ft_encode(p->instr[1], p);
	p->size = p->code[0] + p->code[1] + p->code[2];
	i = 1;
	while (++i <= p->size + 1)
		p->instr[i] = g->arena[(p->pc + i) % MEM_SIZE];
	if (p->code[2] != 1 || !(p->code[1] == 1
			|| p->code[1] == 4) || p->code[0] == 0)
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

static void	ft_ldi_ind_dir(t_glob *g, t_proc *p, int n)
{
	int		cmp;
	t_ldi	var;

	if (p->instr[6] >= 1 && p->instr[6] <= 16)
	{
		cmp = p->pc + (byte_into_short(&(p->instr[2])) % IDX_MOD);
		if (cmp < 0)
			cmp = MEM_SIZE + cmp;
		if (cmp < 0)
			cmp = MEM_SIZE + cmp;
		var.n1 = byte_into_int(&g->arena[cmp]);
		var.n2 = byte_into_short(&(p->instr[4]));
		var.r = p->instr[6];
		ft_core_ldi(g, p, n, var);
	}
	else if (n == 1)
		p->carry = 0;
	p->wait = -1;
	if (g->param->s_pc)
		ft_print_pc(g, p, 7);
	p->pc += 7;
	clear_byte(p->instr);
}

void		ft_core_ldi(t_glob *g, t_proc *p, int n, t_ldi var)
{
	if (n == 0)
		ft_ldi(var.n1 + var.n2, &(p->r[var.r - 1]), g, p);
	else
		ft_lldi(var.n2 + var.n2, &(p->r[var.r - 1]), g, p);
	if (n == 0 && g->param->s_op)
		flag_ldi(p, var.n1, var.n2, var.r);
	else if (n == 1 && g->param->s_op)
		flag_lldi(p, var.n1, var.n2, var.r);
}

void		ft_proc_ldi(t_proc *p, t_glob *g, int n)
{
	if (p->wait == -1)
		p->wait = (n == 0) ? 22 : 47;
	else if (p->wait > 0)
		p->wait -= 1;
	else
	{
		if (!ft_init_ldi(g, p))
			return ;
		if (p->code[0] == 1 && p->code[1] == 1 && p->code[2] == 1)
			ft_ldi_reg_reg(g, p, n);
		else if (p->code[0] == 4 && p->code[1] == 1 && p->code[2] == 1)
			ft_ldi_dir_reg(g, p, n);
		else if (p->code[0] == 2 && p->code[1] == 1 && p->code[2] == 1)
			ft_ldi_ind_reg(g, p, n);
		else if (p->code[0] == 1 && p->code[1] == 4 && p->code[2] == 1)
			ft_ldi_reg_dir(g, p, n);
		else if (p->code[0] == 4 && p->code[1] == 4 && p->code[2] == 1)
			ft_ldi_dir_dir(g, p, n);
		else if (p->code[0] == 2 && p->code[1] == 4 && p->code[2] == 1)
			ft_ldi_ind_dir(g, p, n);
	}
}
