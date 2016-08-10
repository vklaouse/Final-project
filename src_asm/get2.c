/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 15:08:22 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/06 13:01:46 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

int		check_nb_par(t_op *g_op_tab, t_inst *inst, t_srcs **srcs)
{
	t_inst	*tmp;
	t_inst	*tmp_cp;
	t_par	*tmp2;
	int		n;

	if (inst->opcode <= 0)
		return (0);
	n = 0;
	tmp = inst;
	while (tmp)
	{
		tmp2 = tmp->par;
		while (tmp2)
		{
			if (tmp2->p != NULL)
				n++;
			tmp2 = tmp2->next;
		}
		tmp_cp = tmp;
		tmp = tmp->next;
	}
	if (n != g_op_tab->nbr_args)
		add_error1(ft_strjoin("Invalid parameter count for instruction ",
			g_op_tab->mnemonique), srcs);
	return (n);
}

char	*inst_error(int par, t_par *tmp2, t_op *g_op_tab, int i)
{
	return (ft_strjoin(ft_strjoin(ft_strjoin("Invalid parameter ",
						ft_itoa(par)), ft_strjoin(" type",
						par_type(tmp2->type, tmp2))),
				ft_strjoin("for instruction ",
					ft_strjoin(g_op_tab->mnemonique,
						ft_strjoin(" in line ", ft_itoa(i))))));
}

int		check_par_type(t_op *g_op_tab, t_inst *inst, t_srcs **srcs, int i)
{
	int			j;
	t_inst		*tmp;
	t_par		*tmp2;

	tmp = inst;
	tmp2 = tmp->par;
	if (inst->opcode <= 0)
		return (0);
	while (tmp)
	{
		j = 0;
		while (tmp2->next)
		{
			if (!intcmp(g_op_tab->type[j], tmp2->type, g_op_tab->mnemonique,
						tmp2->size) && g_op_tab->type[j] != 7 &&
				(g_op_tab->type[j] != 6 && (tmp2->type != 4)))
				add_error1(inst_error(j, tmp2, g_op_tab, i), srcs);
			else if (!check_lexical(tmp2))
				add_error(tmp2->p, srcs, i);
			tmp2 = tmp2->next;
			j++;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	check_par(t_inst *inst, t_srcs **srcs, int i)
{
	extern t_op	g_op_tab[];
	int			code;

	code = inst->opcode - 1;
	check_par_type(&g_op_tab[code], inst, srcs, i);
	check_nb_par(&g_op_tab[code], inst, srcs);
}

void	add_sum_par(t_inst **inst)
{
	t_inst	*tmp;
	t_par	*tmp2;

	tmp = *inst;
	tmp2 = tmp->par;
	tmp->par_sum += (tmp->opcode == 1 || tmp->opcode == 9 ||
			tmp->opcode == 12 || tmp->opcode == 15) ? 1 : 2;
	while (tmp2)
	{
		tmp->par_sum += tmp2->type;
		tmp2 = tmp2->next;
	}
	tmp->par_sum_t_h += tmp->par_sum;
}
