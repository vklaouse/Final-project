/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 17:23:02 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/10 16:41:13 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

t_par		*create_par(void)
{
	t_par	*par;

	if ((par = (t_par *)malloc(sizeof(t_par))) == NULL)
		ft_exit("Malloc Failure");
	par->p = (NULL);
	par->error = NULL;
	par->size = 0;
	par->type = 0;
	par->pos = 0;
	par->next = NULL;
	return (par);
}

t_inst		*create_inst(int id, int sum, int op, int i)
{
	t_inst	*inst;

	inst = (t_inst *)malloc(sizeof(t_inst));
	if ((inst->opcode = (int)malloc(sizeof(int))) == 0)
		ft_exit("Malloc Failure");
	inst->opcode = op;
	inst->error = NULL;
	inst->par = create_par();
	inst->par_sum = 0;
	inst->par_sum_t_h = sum;
	inst->next = NULL;
	inst->id = id;
	inst->line_nb = i;
	return (inst);
}

t_label		*create_label(char *name, int id, int par_sum)
{
	t_label		*label;

	if ((label = (t_label *)malloc(sizeof(t_label))) == NULL)
		ft_exit("Malloc Failure");
	label->name = ft_strcdup(name, ':');
	label->id = id;
	if (par_sum)
		label->sum = par_sum;
	else
		label->sum = 0;
	label->error = NULL;
	label->next = NULL;
	return (label);
}

t_n_c		*create_name(void)
{
	t_n_c		*n_c;

	if ((n_c = (t_n_c *)malloc(sizeof(t_n_c))) == NULL)
		ft_exit("Malloc Failure");
	n_c->name = NULL;
	n_c->comment = NULL;
	return (n_c);
}

t_srcs		*create_srcs(t_inst *inst, t_label *label, t_n_c *n_c,
		t_error *error)
{
	t_srcs		*srcs;

	if ((srcs = (t_srcs *)malloc(sizeof(t_srcs))) == NULL)
		ft_exit("Malloc Failure");
	srcs->inst = inst;
	srcs->label = label;
	srcs->n_c = n_c;
	srcs->error = error;
	srcs->nb_line = 0;
	srcs->id = 0;
	return (srcs);
}
