/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instr_aff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 20:48:02 by semartin          #+#    #+#             */
/*   Updated: 2016/05/19 20:48:03 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_proc_aff : Print one letter if the instr aff is called. (need option -a)
*/

void	ft_proc_aff(t_proc *p, t_glob *g)
{
	p->instr[1] = g->arena[(p->pc + 1) % MEM_SIZE];
	p->instr[2] = g->arena[(p->pc + 2) % MEM_SIZE];
	ft_encode(p->instr[1], p);
	if (p->code[0] == 1)
	{
		if (g->param->a)
			ft_putchar((char)p->r[p->instr[2] - 1]);
	}
	if (g->param->s_pc)
		ft_print_pc(g, p, 2 + p->code[0]);
	p->pc += 2 + p->code[0];
	p->wait = -1;
	clear_byte(p->instr);
}
