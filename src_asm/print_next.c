/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_next.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 13:36:16 by jschotte          #+#    #+#             */
/*   Updated: 2016/06/13 15:01:01 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"

int		print_direct(t_encode *e, t_par *par, int fd)
{
	if (e->op == 11 || e->op == 14 || e->op == 9
			|| e->op == 10 || e->op == 15 || e->op == 12)
		return (print_int(ft_atoi(ft_strsub(par->p, 1,
							ft_strlen(par->p) - 1)), fd));
	else
		return (print_adressnum(ft_atoi(ft_strsub(par->p, 1,
							ft_strlen(par->p) - 1)), fd));
}

int		ft_print_par(t_par *par, t_encode *e, t_label *label, int fd)
{
	if (par->size == 4)
		return (print_int(*(int*)par->p, fd));
	else if (ft_strcmp(ft_strsub(par->p, 0, 1), "r") == 0
			&& ft_strlen(par->p) > 1)
	{
		ft_putchar_fd(ft_atoi(ft_strsub(par->p, 1,
						ft_strlen(par->p) - 1)), fd);
		return (1);
	}
	else if (ft_strcmp(ft_strsub(par->p, 0, 1), "%") == 0
			|| ft_strcmp(ft_strsub(par->p, 0, 1), ":") == 0)
	{
		if (ft_strcmp(ft_strsub(par->p, 1, 1), ":") == 0)
			return (print_int(get_difflabel(label, ft_strsub(par->p, 2,
								ft_strlen(par->p) - 2)) - e->count, fd));
		else if (ft_strcmp(ft_strsub(par->p, 0, 1), ":") == 0)
			return (print_int(get_difflabel(label, ft_strsub(par->p, 1,
								ft_strlen(par->p) - 1)) - e->count, fd));
		else
			return (print_direct(e, par, fd));
	}
	else
		return (0);
}

char	ft_puissance(char nb, int puissance)
{
	char	total;
	int		i;

	i = 0;
	total = 1;
	while (i < puissance)
	{
		total *= nb;
		i++;
	}
	return (total);
}

void	print_inst(t_label *label, t_inst *inst, int pfd)
{
	t_par		*tmp2;
	t_encode	*env;

	if (!(env = malloc(sizeof(t_encode))))
		ft_exit("Allocation error");
	env->count = 0;
	while (inst)
	{
		env->tmp = 1;
		env->op = inst->opcode;
		ft_putchar_fd(env->op, pfd);
		if (env->op != 1 && env->op != 9 && env->op != 12 && env->op != 15)
		{
			ft_putchar_fd(get_octet_code(inst->par), pfd);
			env->tmp++;
		}
		tmp2 = inst->par;
		while (tmp2->p)
		{
			env->tmp += ft_print_par(tmp2, env, label, pfd);
			tmp2 = tmp2->next;
		}
		env->count += env->tmp;
		inst = inst->next;
	}
}

void	print_header(t_inst *inst, t_n_c *n_c, int pfd)
{
	print_magic(pfd);
	print_str(ft_strsub(n_c->name, 1, ft_strlen(n_c->name) - 2),
			(int)PROG_NAME_LENGTH, pfd);
	print_size(inst, pfd);
	print_str(ft_strsub(n_c->comment, 1, ft_strlen(n_c->comment) - 2),
			(int)COMMENT_LENGTH, pfd);
	print_str("", 4, pfd);
}
