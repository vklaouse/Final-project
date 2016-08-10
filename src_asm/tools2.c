/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 17:24:22 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/06 13:10:04 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

int		check_label_chars(char c)
{
	int		i;
	int		n;

	n = 0;
	i = 0;
	while (LABEL_CHARS[i])
	{
		if (c == LABEL_CHARS[i])
			n++;
		i++;
	}
	if (n == 0)
		return (0);
	return (1);
}

int		verify_inst(char *str)
{
	int		i;
	char	*lab;

	if (str == NULL)
		return (0);
	lab = ft_strdup("abcdefghijklmnopqrstuvwxyz_0123456789:;%-#,");
	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == ';')
			break ;
		if (!ft_strchr(lab, str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*par_type(int type, t_par *par)
{
	if (par->size == 4)
		return (" indirect ");
	if (type == 1)
		return (" register ");
	if (type == 2)
		return (" direct ");
	if (type == 4)
		return (" indirect ");
	if (type == 8)
		return (" lab ");
	return ("");
}

int		intcmp(int a, int b, char *op, int sz)
{
	int pair_a;
	int pair_b;

	pair_a = 0;
	pair_b = 0;
	if (a == 0 && b != 0)
		return (0);
	if ((a == 3 || a == 5) && b == 2 && (ft_strcmp(op, "sti") && sz == 4))
		return (1);
	else if ((a == 3 || a == 5) && b == 2 && (!ft_strcmp(op, "sti") && sz != 4))
		return (1);
	if ((a == 3 || a == 5) && b == 2 && (!ft_strcmp(op, "st") ||
				!ft_strcmp(op, "ldi") || !ft_strcmp(op, "lldi")))
		return (1);
	if (a % 2 == 0)
		pair_a = 1;
	if (b % 2 == 0)
		pair_b = 1;
	if (pair_a == pair_b)
		return (1);
	return (0);
}

int		verify_label_letter(char *str)
{
	int		i;
	char	*lab;

	if (ft_strlen(str) == 1)
		return (0);
	lab = ft_strdup("abcdefghijklmnopqrstuvwxyz_0123456789");
	i = 0;
	while (str[i] && str[i] != ':')
	{
		if (!ft_strchr(lab, str[i]))
			return (0);
		i++;
	}
	return (1);
}
