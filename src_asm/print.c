/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 16:36:00 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/10 16:39:17 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

void	print_n_label(t_n_c *n_c, t_label *label)
{
	t_n_c	*tmp4;
	t_label	*tmp2;

	tmp4 = n_c;
	tmp2 = label;
	if (tmp4)
	{
		ft_put("\nName : ", GREEN);
		ft_putstr(tmp4->name);
		ft_put("\nComment : ", GREEN);
		ft_putstr(tmp4->comment);
	}
	ft_put("\n\n=======LABEL=======\n", RED);
	while (tmp2)
	{
		ft_put("\nLabel : ", YELLOW);
		ft_putstr(tmp2->name);
		if (tmp2->error != NULL)
		{
			ft_putstr("\nLabel ERROR : ");
			ft_putstr(tmp2->error);
		}
		ft_putchar('\n');
		tmp2 = tmp2->next;
	}
}

void	print_par(t_inst *tmp, int i)
{
	while (tmp->par)
	{
		if (tmp->par->size == 4)
		{
			ft_put("  Par ", RED);
			ft_put(ft_strjoin(ft_itoa(i), " : "), RED);
			ft_putnbr(*(int *)tmp->par->p);
		}
		else if (tmp->par->p != NULL)
		{
			ft_put("  Par ", RED);
			ft_put(ft_strjoin(ft_itoa(i), " : "), RED);
			ft_putstr((char *)tmp->par->p);
		}
		if (tmp->par->error != NULL)
		{
			ft_putstr(" | ERROR : ");
			ft_putstr(tmp->par->error);
			ft_putchar('\n');
		}
		tmp->par = tmp->par->next;
		i++;
	}
}

void	print(t_inst *inst, t_label *label, t_n_c *n_c)
{
	t_inst	*tmp;
	int		i;

	i = 0;
	tmp = inst;
	print_n_label(n_c, label);
	ft_put("\n=======INSTRUCTIONS=======\n\n", RED);
	while (tmp)
	{
		i = 0;
		ft_put("ID : ", GREEN);
		ft_putnbr(tmp->id);
		ft_put("  OPCODE : ", YELLOW);
		ft_putnbr(tmp->opcode);
		print_par(tmp, i);
		if (tmp->error)
		{
			ft_putstr(" | INST ERROR : ");
			ft_putstr(tmp->error);
		}
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void	ft_print_error(t_srcs *srcs)
{
	t_error		*tmp3;

	tmp3 = srcs->error;
	while (tmp3)
	{
		ft_putendl(tmp3->str);
		tmp3 = tmp3->next;
	}
}
