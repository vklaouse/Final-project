/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 15:34:56 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/10 16:35:46 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

int		add_to_srcs(char *str, char **split, int id, t_srcs **srcs)
{
	char *s;

	s = epur_str(str);
	if (ft_strchr(split[0], ':'))
	{
		get_label(str, srcs, id, ft_get_lst_sum(&(*srcs)->inst));
		return (inst_or_error(str, split, (*srcs)->nb_line, srcs));
	}
	else if ((ft_strchr(str, ',') || (verify_inst(split[1]) && !split[2]))
		&& ft_wordcount(split) == ft_charcount(str, ',') + 2 && is_inst(str))
	{
		add_inst(s, srcs, id, (*srcs)->nb_line);
		return (check_instru(srcs, (*srcs)->nb_line, split[0]));
	}
	return (add_error(str, srcs, (*srcs)->nb_line));
}

int		ft_check_and_add(char *str, t_srcs **srcs, int i)
{
	static int	id = -1;
	char		**split;
	char		*s;

	(*srcs)->nb_line = i;
	if ((ft_strstr(str, ".name") || ft_strstr(str, ".comment") ||
		ft_strchr(str, '"') || empty_line(str)) && id == -1)
		return (get_n_c_comment(str, (*srcs)->n_c, srcs, i));
	else if (is_hash(str) || is_ponct(str) || ft_strchr(str, '"')
		|| empty_line(str) || (!is_inst(str) && !is_label(str)))
		return (1);
	else
	{
		id++;
		s = epur_str(str);
		split = ft_strsplit2(s, ',');
		return (add_to_srcs(str, split, id, srcs));
	}
}

int		name_cmp(t_par *tmp3, int y, t_srcs **srcs)
{
	t_label	*tmp_lab;
	int		n;
	int		i;

	tmp_lab = (*srcs)->label;
	n = 0;
	i = 0;
	if (tmp3->size == 1 && ft_strstr((char *)tmp3->p, ":"))
	{
		while (tmp_lab)
		{
			if (!ft_strcmp(ft_strchr((char*)tmp3->p, ':') + 1,
				tmp_lab->name))
				i++;
			tmp_lab = tmp_lab->next;
		}
		if (i == 0)
		{
			add_error1(ft_strjoin(ft_strjoin("No such label ",
							ft_strchr((char*)tmp3->p, ':') + 1),
						ft_strjoin(tmp3->error, write_inst_error(tmp3->pos
								+ ft_strlen((char*)tmp3->p), y))), srcs);
		}
	}
	return (i);
}

void	check_label(int i, t_srcs **srcs)
{
	t_inst	*tmp;
	t_par	*tmp3;

	(void)i;
	if ((tmp = (*srcs)->inst) == NULL)
		return ;
	tmp3 = tmp->par;
	while (tmp)
	{
		tmp3 = tmp->par;
		while (tmp3)
		{
			name_cmp(tmp3, tmp->line_nb, srcs);
			tmp3 = tmp3->next;
		}
		tmp = tmp->next;
	}
	return ;
}

int		parsing(char *str, t_srcs **srcs)
{
	char		*line;
	int			fd;
	static int	i = 1;

	line = NULL;
	if ((fd = open(str, O_RDONLY)) < 0)
		return (0);
	while (get_next_line(fd, &line) > 0)
		i += ft_check_and_add(line, srcs, i);
	if (i == 0)
		return (0);
	check_label(i, srcs);
	check_n_c(srcs);
	check_srcs(srcs);
	return (i);
}
