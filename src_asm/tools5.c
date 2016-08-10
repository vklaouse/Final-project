/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 13:11:44 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/14 15:27:45 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

int		is_register(char *s)
{
	char	*r;
	int		i;

	i = 0;
	r = ft_strsub(s, 1, 2);
	if (r == NULL && ft_isdigit(s[1]) && s[0] == 'r'
		&& ft_strlen(s) <= 3 && s[1] != '0')
		return (1);
	else if (r == NULL)
		return (0);
	while (r[i])
	{
		if (!ft_isdigit(r[i]))
			return (0);
		i++;
	}
	if (i > 2 || ft_atoi(r) == 0)
		return (0);
	if (ft_atoi(r) == 0 || ft_atoi(r) > 99 ||
		ft_strlen(r) > 3 || ft_strlen(s) > 3)
		return (0);
	else
		return (1);
}

int		is_hash(char *str)
{
	int		i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (str[i] == '#');
}

int		is_ponct(char *str)
{
	int		i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (str[i] == ';');
}

int		not_comment(char *str)
{
	int		i;
	int		j;
	int		z;

	i = 0;
	j = 0;
	z = 0;
	while (str[i])
	{
		if (str[i] == ';')
			j = i;
		else if (str[i] == ':')
			z = i;
		i++;
	}
	return (j < z);
}

int		is_label(char *str)
{
	int		i;

	i = 0;
	if (!ft_strchr(str, ':'))
		return (0);
	while (str[i] != ':')
		i++;
	return (ft_isspace(str[i - 1]));
}
