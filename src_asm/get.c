/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 17:04:10 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/10 16:11:13 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

int		check_inst(char *str)
{
	static char *op_tab[16] = {"live", "ld", "st", "add", "sub", "and",
	"or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"};
	int			i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(str, op_tab[i]))
		{
			return (i + 1);
		}
		i++;
	}
	return (-1);
}

char	*error_str(char *str, int i)
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

int		check_lexical(t_par *par)
{
	if (!ft_strcmp((char*)par->p, ":%"))
		return (0);
	if (par->size == 4)
	{
		return (1);
	}
	if (*(char*)par->p == '%' && *((char*)par->p + 1) != ':'
		&& *((char*)par->p + 1) != '-' && !ft_isdigit(*((char*)par->p + 1)))
		return (0);
	if (!*(char*)par->p || *(char*)par->p == '%' || *(char*)par->p == '-' ||
		*(char*)par->p == ':' || is_register((char*)par->p) ||
		ft_isspace(*(char*)par->p))
	{
		return (1);
	}
	else
		return (0);
}

int		get_opcode(char *str, t_inst *inst, int i, t_srcs **srcs)
{
	while (ft_isspace(*str))
		str++;
	if ((inst->opcode = check_inst(str)) == -1)
	{
		add_error1(ft_strjoin("Invalid instruction at token [TOKEN]",
			error_str(str, i)), srcs);
		return (-1);
	}
	return (1);
}

int		get_type(char *s, int opcode)
{
	if (s == NULL)
		return (-1);
	if (s[0] == 'r')
		return (T_REG);
	else if (ft_strchr(s, '%') || ft_strchr(s, ':'))
	{
		if (ft_isdigit(*(s + 1)) || s[1] == '-')
		{
			if (opcode == 10 || opcode == 11 || opcode == 9
				|| opcode == 12 || opcode == 14 || opcode == 15)
				return (T_DIR);
			return (T_IND);
		}
		if (opcode == 10 || opcode == 11)
			return (T_DIR);
		else
			return (T_DIR);
	}
	else if (ft_atoi(s) != 0 || !ft_strcmp(s, "0"))
		return (T_DIR);
	return (-1);
}
