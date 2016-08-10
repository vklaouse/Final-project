/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 17:11:47 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/10 16:12:39 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

int		get_value(char *str, void **par, int *size)
{
	int		*n;

	if ((n = (int *)malloc(sizeof(n))) == NULL)
		ft_exit("Malloc Failure");
	while (ft_isspace(*str))
		str++;
	*n = ft_atoi(str);
	*par = n;
	*size = 4;
	return (1);
}

int		get_par_lst(char *str, t_par *par, int opcode)
{
	char	*s;
	int		i;
	int		*n;

	if ((n = (int *)malloc(sizeof(n))) == NULL)
		ft_exit("Malloc Failure");
	while (ft_isspace(*str))
		str++;
	if ((*n = ft_atoi(str)) != 0 || str[0] == '0')
	{
		par->size = 4;
		par->type = get_type(str, opcode);
		return (get_value(str, &par->p, &par->size));
	}
	s = ft_strnew(ft_strlen(str));
	while (ft_isspace(*str))
		str++;
	i = ft_strnchr(str, ',');
	if (i != 0)
		par->p = ft_strdup(ft_strncpy(s, str, i));
	else
		par->p = ft_strdup(ft_strdup(str));
	par->size = 1;
	par->type = get_type(par->p, opcode);
	return (1);
}

void	get_par(char **split, t_srcs **srcs, int i)
{
	int		index;
	t_inst	*tmp;
	t_par	*tmp2;

	tmp = (*srcs)->inst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->par = create_par();
	tmp2 = tmp->par;
	index = 1;
	while (split[index] && !ft_strchr(split[index], ';'))
	{
		get_par_lst(split[index], tmp2, tmp->opcode);
		tmp2->pos = get_pos(tmp2) + ft_strlen(split[index - 1]);
		tmp2->next = create_par();
		tmp2 = tmp2->next;
		index++;
	}
	check_par(tmp, srcs, i);
	add_sum_par(&tmp);
}

int		get_label(char *str, t_srcs **srcs, int id, int par_sum)
{
	t_label	*tmp;

	while (ft_isspace(*str))
		str++;
	tmp = (*srcs)->label;
	if (!verify_label_letter(str))
		return (add_error(str, srcs, (*srcs)->nb_line));
	if ((*srcs)->label == NULL)
		(*srcs)->label = create_label(str, id, par_sum);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_label(str, id, par_sum);
	}
	return (1);
}

int		get_n_c_comment(char *str, t_n_c *n_c, t_srcs **srcs, int i)
{
	if ((*srcs)->n_c == NULL)
		(*srcs)->n_c = create_name();
	if (there_is_char(str) || (ft_strstr(str, ".name") && !ft_strchr(str, '"'))
		|| bad_n_c(str))
		return (add_error(str, srcs, i));
	if ((ft_strstr(str, ".name") || (!empty_line(str) &&
		nb_char((*srcs)->n_c->name, '"') != 2)) && !ft_strstr(str, ".comment"))
	{
		if (nb_char(str, '"') == 2 && !ft_strstr(str, ".name"))
			return (0);
		if ((*srcs)->n_c->name && nb_char((*srcs)->n_c->name, '"') == 1)
		{
			(*srcs)->n_c->name = ft_strjoin((*srcs)->n_c->name, str);
			return (1);
		}
		while (*str != '"')
			str++;
		if (nb_char((*srcs)->n_c->name, '"') == 0)
			(*srcs)->n_c->name = ft_strdup(str);
	}
	else if ((ft_strstr(str, ".comment") || !empty_line(str) ||
		nb_char((*srcs)->n_c->comment, '"') == 1) && (*srcs)->n_c->name)
		(*srcs)->n_c->comment = get_name(str, n_c, srcs);
	return (1);
}
