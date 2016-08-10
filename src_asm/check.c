/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 11:29:38 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/13 11:29:50 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

char	*test(char *str, int i)
{
	char	*s;
	char	*s2;
	int		c;

	s = NULL;
	s2 = ft_strnew(10);
	c = nb_number(i);
	s2 = ft_str_join_char(s2, '[');
	while (c++ < 3)
		s2 = ft_str_join_char(s2, '0');
	s2 = ft_cjoin(s2, ft_itoa(i));
	s2 = ft_str_join_char(s2, ':');
	c = nb_number(ft_strlen(str) + 1);
	while (c++ < 3)
		s2 = ft_str_join_char(s2, '0');
	s2 = ft_cjoin(s2, ft_itoa(ft_strlen(str) + 1));
	s2 = ft_str_join_char(s2, ']');
	return (s2);
}

int		ft_charcount(char *s, char c)
{
	int n;

	n = 0;
	while (*s && *s != '#' && *s != ';')
	{
		if (*s == c)
			n++;
		s++;
	}
	return (n);
}

int		is_inst(char *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (ft_isspace(*s) && *s)
		s++;
	while (!ft_isspace(*s) && *s)
	{
		if (*s == ',')
			return (0);
		s++;
	}
	while (ft_isspace(*s) && *s)
		s++;
	if (*s == ',')
		return (0);
	return (1);
}

int		ft_wordcount(char **s)
{
	int		i;
	int		n;

	i = (ft_strchr(s[0], ':')) ? 1 : 0;
	n = (ft_strchr(s[0], ':')) ? 1 : 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i - n);
}

int		inst_or_error(char *str, char **split, int i, t_srcs **srcs)
{
	char *s;

	s = epur_str(str);
	if (split[1] && verify_inst(split[1]) && ft_wordcount(split) ==
		(ft_charcount(ft_strchr(str, ':') + 1, ',') + 2) &&
		is_inst(ft_strchr(str, ':') + 1))
		return (add_inst(ft_strchr(s, ':') + 1, srcs, (*srcs)->id++, i));
	else if (split[1] && verify_inst(split[1]) && (ft_wordcount(split)
		!= (ft_charcount(ft_strchr(str, ':') + 1, ',') + 2) ||
		!is_inst(ft_strchr(str, ':') + 1)))
		return (add_error(str, srcs, i));
	return (1);
}
