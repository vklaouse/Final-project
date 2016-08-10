/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 16:45:10 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/13 11:31:06 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

void	ft_exit(char *str)
{
	ft_putendl_fd(str, 2);
	exit(0);
}

void	ft_put(char *str, char *color)
{
	ft_putstr(color);
	ft_putstr(str);
	ft_putstr("\033[0m");
}

void	check_srcs(t_srcs **srcs)
{
	if ((*srcs)->inst == NULL)
		add_error1("No Insrtuction", srcs);
}

char	*ft_strcdup(const char *s1, char c)
{
	char	*s2;
	int		i;
	int		nb;

	i = 0;
	nb = ft_strlen(s1);
	if (nb == 0)
	{
		if ((s2 = malloc(sizeof(*s1))) == NULL)
			ft_exit("Malloc Failure");
		*s2 = 0;
		return (s2);
	}
	if ((s2 = malloc(sizeof(*s1) * (nb + 1))) == NULL)
		ft_exit("Malloc Failure");
	while (i < nb && s1[i] != c)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

void	free_all(t_srcs **srcs)
{
	if ((*srcs)->inst)
		free((*srcs)->inst);
	if ((*srcs)->label)
		free((*srcs)->label);
	if ((*srcs)->n_c)
		free((*srcs)->n_c);
	if ((*srcs)->error)
		free((*srcs)->error);
}
