/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 17:25:44 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/10 16:42:38 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

int		get_pos(t_par *tmp)
{
	if (tmp->size == 4)
		return (nb_number(*(int *)tmp->p));
	else if (tmp->p != NULL)
		return (ft_strlen((char *)tmp->p));
	return (0);
}

int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\n')
		return (1);
	else
		return (0);
}

char	*epur_str(char *str)
{
	int		i;
	int		j;
	char	*dest;

	if ((dest = (char*)malloc(sizeof(char*) * ft_strlen(str) + 1)) == NULL)
		ft_exit("Malloc Failure");
	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '#' && str[i] != ';')
	{
		while (ft_isspace(str[i]) && str[i])
			i++;
		while (ft_isspace(str[i]) == 0 && str[i] != ',' && str[i])
			dest[j++] = str[i++];
		while ((ft_isspace(str[i]) && str[i]) || str[i] == ',')
			i++;
		if (str[i] != ',' && str[i] != '\0')
		{
			dest[j] = ',';
			j++;
		}
	}
	dest[j] = '\0';
	return (dest);
}

int		ft_get_lst_sum(t_inst **inst)
{
	t_inst	*tmp;

	tmp = *inst;
	if (!tmp)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->par_sum_t_h);
}

int		add_inst(char *str, t_srcs **srcs, int id, int i)
{
	t_inst	*tmp;
	char	**split;

	split = ft_strsplit2(str, ',');
	tmp = (*srcs)->inst;
	if ((tmp = (*srcs)->inst) == NULL)
		(*srcs)->inst = create_inst(id, 0, check_inst(split[0]), i);
	else
	{
		tmp = (*srcs)->inst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_inst(id, tmp->par_sum_t_h, check_inst(split[0]), i);
	}
	get_par(split, srcs, i);
	return (1);
}
