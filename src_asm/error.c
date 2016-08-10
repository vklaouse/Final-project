/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 13:28:42 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/10 16:10:17 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

t_error	*create_error(char *str)
{
	t_error		*error;

	if ((error = (t_error *)malloc(sizeof(t_error))) == NULL)
		ft_exit("Malloc Failure");
	error->str = ft_strdup(str);
	error->next = NULL;
	return (error);
}

char	*write_inst_error(int x, int y)
{
	char	*s;
	char	*s2;
	int		c;

	s = NULL;
	s2 = ft_strnew(10);
	c = nb_number(y);
	s2 = ft_str_join_char(s2, '[');
	while (c++ < 3)
		s2 = ft_str_join_char(s2, '0');
	s2 = ft_cjoin(s2, ft_itoa(y));
	s2 = ft_str_join_char(s2, ':');
	c = nb_number(x);
	while (c++ < 3)
		s2 = ft_str_join_char(s2, '0');
	s2 = ft_cjoin(s2, ft_itoa(x));
	s2 = ft_str_join_char(s2, ']');
	s = ft_cjoin(ft_strdup(" while attempting to dereference token [TOKEN]"),
		s2);
	return (s);
}

char	*write_error(char *str, int i)
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
	s = ft_cjoin(ft_strdup("Syntax error at token [TOKEN]"), s2);
	return (s);
}

int		add_error(char *str, t_srcs **srcs, int i)
{
	t_error		*tmp;

	(void)i;
	if (empty_line(str) || str == NULL)
		return (1);
	tmp = (*srcs)->error;
	if ((*srcs)->error == NULL)
		(*srcs)->error = create_error(write_error(str, i));
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_error(write_error(str, i));
	}
	return (1);
}

int		add_error1(char *str, t_srcs **srcs)
{
	t_error		*tmp;

	if (empty_line(str) || str == NULL)
		return (1);
	tmp = (*srcs)->error;
	if ((*srcs)->error == NULL)
		(*srcs)->error = create_error(str);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_error(str);
	}
	return (1);
}
