/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 16:43:42 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/10 16:45:01 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

int		nb_char(char *s, char c)
{
	int		i;
	int		n;

	if (s == NULL)
		return (0);
	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			n++;
		i++;
	}
	return (n);
}

int		there_is_char(char *s)
{
	if (s == NULL)
		return (0);
	if (nb_char(s, '"') == 1 || empty_line(s))
		return (0);
	if (*s == '"')
		s++;
	while (*s != '"')
		s++;
	if (*s == '"')
		s++;
	while (*s != '"')
		s++;
	if (*s == '"')
		s++;
	while (ft_isspace(*s) && *s)
		s++;
	if (*s)
		return (1);
	return (0);
}

int		check_instru(t_srcs **srcs, int i, char *s)
{
	t_inst *tmp;

	tmp = (*srcs)->inst;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->opcode == -1)
		add_error1(ft_strjoin("Invalid instruction at token [TOKEN]",
			test(s, i)), srcs);
	return (1);
}

char	*get_name(char *str, t_n_c *n_c, t_srcs **srcs)
{
	if ((*srcs)->n_c->comment && nb_char((*srcs)->n_c->comment, '"') == 1)
		return (ft_strjoin(ft_str_join_char(n_c->comment, 10), str));
	while (*str != '"')
		str++;
	return (ft_strdup(str));
}

void	check_n_c(t_srcs **srcs)
{
	if (nb_char((*srcs)->n_c->name, '"') != 2)
		add_error1("Lexical Name Error", srcs);
	else if (nb_char((*srcs)->n_c->comment, '"') != 2)
		add_error1("Lexical Comment Error", srcs);
	else if ((*srcs)->n_c->comment == NULL)
		add_error1("No comment", srcs);
	else if ((*srcs)->n_c->name == NULL)
		add_error1("No name", srcs);
	else if (ft_strlen((*srcs)->n_c->name) - 2 > 128)
		add_error1("Bad lenght name", srcs);
}
