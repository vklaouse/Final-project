/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instr_zjmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 16:04:27 by semartin          #+#    #+#             */
/*   Updated: 2016/05/19 16:04:28 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	zjmp_show_op : If option -op : Add the operation to the buffer
**					that will be printed on screen
**	---------------------------------------------------------------------------
**	proc_zjmp : Change the pc : Add the param to it. --> Call change PC
**				Only when the carry == 1
**				--> Used to make loop
*/

static void	zjmp_show_op(t_proc *p)
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
	ft_itoa_cpy(p->number, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | zjmp ");
	ft_itoa_cpy((byte_into_short(&(p->instr[1]))), (tmp = tmp + 8));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " ");
	if (p->carry == 1)
		ft_strcpy(++tmp, "FAILED");
	else
		ft_strcpy(++tmp, "OK");
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), "\n");
	ft_buffer_screen(s, 0);
	free(s);
}

static void	change_pc(t_proc *p, t_glob *g)
{
	if (p->carry == 0)
		p->pc = p->pc + (byte_into_short(&(p->instr[1])) % IDX_MOD);
	else
	{
		if (g->param->s_pc)
			ft_print_pc(g, p, 3);
		p->pc += 3;
	}
	if (p->pc < 0)
		p->pc = MEM_SIZE + p->pc;
}

void		ft_proc_zjmp(t_proc *p, t_glob *g)
{
	int i;

	if (p->wait == -1)
		p->wait = 17;
	else if (p->wait > 0)
		p->wait -= 1;
	else
	{
		i = 0;
		while (++i < 3)
			p->instr[i] = g->arena[(p->pc + i) % MEM_SIZE];
		if (g->param->s_op)
			zjmp_show_op(p);
		change_pc(p, g);
		clear_byte(p->instr);
		p->wait = -1;
	}
}
