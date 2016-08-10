/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instr_ld.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 12:08:00 by semartin          #+#    #+#             */
/*   Updated: 2016/05/19 12:08:01 by semartin         ###   ########.fr       */
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
**	ld_fill : Put the value previously calculed (in nb) into the right register
**				Put the carry at 0 if instr isn't correct or if nb != 0
**	---------------------------------------------------------------------------
**	ld_show_op : If option -op : Add the operation to the buffer
**					that will be printed on screen
**	---------------------------------------------------------------------------
**	ld_core : Put the value of the register (2nd param) into the first param
**					1st param can be either a register or an adress
**					if it's an adress lld will acces further than IDX_MOD
**					ld won't and will loop modulo IDX_MOD instead
**	---------------------------------------------------------------------------
**	ft_proc_ld : Called ld's fncts and wait the right number of cicle
**					On ld the process execute on 5 cycles, on lld 10
*/

static int	ft_init_ld(t_glob *g, t_proc *p)
{
	int i;

	p->instr[1] = g->arena[(p->pc + 1) % MEM_SIZE];
	ft_encode(p->instr[1], p);
	p->size = p->code[0] + p->code[1];
	i = 1;
	while (++i <= p->size + 1)
		p->instr[i] = g->arena[(p->pc + i) % MEM_SIZE];
	if (p->code[1] != 1 || !(p->code[0] == 2 || p->code[0] == 4))
	{
		p->wait = -1;
		if (g->param->s_pc)
			ft_print_pc(g, p, 2 + p->code[0] + p->code[1]);
		p->pc += (2 + p->code[0] + p->code[1]);
		clear_byte(p->instr);
		return (0);
	}
	return (1);
}

static void	ld_fill(t_proc *p, int max, int nb)
{
	if (p->instr[max] < 1 && p->instr[max] > 16)
		p->carry = 0;
	else
	{
		p->r[p->instr[max] - 1] = nb;
		if (nb == 0)
			p->carry = 0;
		else
			p->carry = 1;
	}
}

static void	ld_show_op(t_proc *p, int max, int mod, int cmp)
{
	int		i;
	int		nb;
	char	*s;
	char	*tmp;

	if (!(s = malloc(sizeof(*s) * 64)))
		ft_error("Allocation Error : Insufficient memory");
	tmp = s;
	i = 0;
	nb = number_digit(p->number);
	ft_strcpy(tmp++, "P");
	while (i++ < 5 - nb)
		ft_strcpy(tmp++, " ");
	ft_itoa_cpy(p->number, tmp);
	if (mod == IDX_MOD)
		ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | ld ");
	else
		ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | lld ");
	ft_itoa_cpy(cmp, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " r");
	ft_itoa_cpy(p->instr[max], (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), "\n");
	ft_buffer_screen(s, 0);
	free(s);
}

static void	core_ld(t_glob *g, t_proc *p, int mod, int max)
{
	int cmp;

	if (p->size == 3
		&& p->instr[4] >= 1 && p->instr[4] <= 16)
	{
		cmp = (p->pc + (byte_into_short(&(p->instr[2])) % mod));
		if (cmp < 0)
			cmp = MEM_SIZE + cmp;
		cmp = byte_into_int(&(g->arena[cmp]));
		max = 4;
		ld_fill(p, max, cmp);
	}
	else if (p->size == 5 && p->instr[6] >= 1 && p->instr[6] <= 16)
	{
		cmp = byte_into_int(&(p->instr[2]));
		max = 6;
		ld_fill(p, max, cmp);
	}
	if (g->param->s_op && p->instr[max] >= 1
						&& p->instr[max] <= 16 && max != 0)
		ld_show_op(p, max, mod, cmp);
	if (g->param->s_pc)
		ft_print_pc(g, p, 2 + p->code[0] + p->code[1]);
}

void		ft_proc_ld(t_proc *p, t_glob *g, int n)
{
	int mod;
	int max;

	if (p->wait == -1)
		p->wait = (n == 0) ? 2 : 7;
	else if (p->wait > 0)
		p->wait -= 1;
	else
	{
		max = 0;
		if (!ft_init_ld(g, p))
			return ;
		mod = (n == 0) ? IDX_MOD : MEM_SIZE;
		core_ld(g, p, mod, max);
		clear_byte(p->instr);
		p->pc += (2 + p->code[0] + p->code[1]);
		p->wait = -1;
	}
}
