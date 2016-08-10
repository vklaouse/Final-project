/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 12:28:01 by semartin          #+#    #+#             */
/*   Updated: 2016/05/24 16:17:27 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_what_instr_2 : Call the right fnct depending on the content of instr[0]
**	---------------------------------------------------------------------------
** 	ft_what_instr : Call the right fnct depending on the content of instr[0]
**	---------------------------------------------------------------------------
**	ft_algo : Run down the all t_list, for each process :
**				- If The content of instr[0] is not an instr (1->16)
**					--> Increase pc by one
**					--> Fill the new instr[0] with arena[pc]
**				- If the content of instr[0] is an instr
**					--> Call ft_what_instr
*/

static void	ft_what_instr_2(t_proc *p, t_glob *g)
{
	if (p->instr[0] == 8)
		ft_proc_bit(p, g, 2);
	else if (p->instr[0] == 9)
		ft_proc_zjmp(p, g);
	else if (p->instr[0] == 10)
		ft_proc_ldi(p, g, 0);
	else if (p->instr[0] == 11)
		ft_proc_sti(p, g);
	else if (p->instr[0] == 12)
		ft_proc_fork(p, g, 0);
	else if (p->instr[0] == 13)
		ft_proc_ld(p, g, 1);
	else if (p->instr[0] == 14)
		ft_proc_ldi(p, g, 1);
	else if (p->instr[0] == 15)
		ft_proc_fork(p, g, 1);
	else if (p->instr[0] == 16)
		ft_proc_aff(p, g);
	else
	{
		p->pc += 1;
		clear_byte(p->instr);
	}
}

static void	ft_what_instr(t_proc *p, t_glob *g)
{
	if (p->instr[0] == 1)
		ft_proc_live(p, g);
	else if (p->instr[0] == 2)
		ft_proc_ld(p, g, 0);
	else if (p->instr[0] == 3)
		ft_proc_st(p, g);
	else if (p->instr[0] == 4)
		ft_proc_op(p, g, 0);
	else if (p->instr[0] == 5)
		ft_proc_op(p, g, 1);
	else if (p->instr[0] == 6)
		ft_proc_bit(p, g, 0);
	else if (p->instr[0] == 7)
		ft_proc_bit(p, g, 1);
	else
		ft_what_instr_2(p, g);
}

void		ft_algo(t_glob *g)
{
	t_list	*tmp;
	t_proc	*p;

	tmp = g->begin_lst;
	while (tmp != NULL)
	{
		p = tmp->content;
		if (p->instr[0] == 0)
		{
			if (g->arena[p->pc % MEM_SIZE] > 0
				&& g->arena[p->pc % MEM_SIZE] <= 16)
				p->instr[0] = g->arena[p->pc % MEM_SIZE];
			else
			{
				if (p->pc == MEM_SIZE - 1)
					p->pc = 0;
				else
					p->pc += 1;
			}
		}
		else
			ft_what_instr(p, g);
		p = NULL;
		tmp = tmp->next;
	}
}
