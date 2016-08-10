/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 17:12:27 by vklaouse          #+#    #+#             */
/*   Updated: 2016/05/11 16:55:48 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

static void	name_size(t_glob *g, int j, int i)
{
	if (j == TO_COM)
		g->cnt = 0;
	if (j < TO_CHAMP && g->cnt != -1)
	{
		if (g->bcode[i][j] == 0x00)
			g->cnt = -1;
		else
			g->champ[i]->comment[g->cnt++] = g->bcode[i][j] + 'a';
	}
	else if (j < TO_CHAMP + g->champ[i]->champ_size)
	{
		if (j == TO_CHAMP)
			g->cnt = 0;
		g->champ[i]->prog[g->cnt++] = g->bcode[i][j];
	}
}

static void	champ(t_glob *g, int j, int i)
{
	if (j < TO_SIZE && g->cnt != -1)
	{
		if (g->bcode[i][j] == 0x00)
			g->cnt = -1;
		else
			g->champ[i]->name[g->cnt++] = g->bcode[i][j];
	}
	else if (j < TO_COM)
	{
		if (j == TO_SIZE)
			g->cnt = 0;
		g->champ[i]->champ_size = byte_into_long(&(g->bcode[i][TO_SIZE]));
	}
	else
		name_size(g, j, i);
}

void		ft_parsing(t_glob *g)
{
	int	i;
	int	j;
	int magic;

	i = 0;
	while (i < g->nb_champ)
	{
		j = 0;
		g->cnt = 0;
		while (g->champ[i]->size > j)
		{
			if (j < 4)
			{
				magic = byte_into_int(&(g->bcode[i][0]));
				if (magic != COREWAR_EXEC_MAGIC)
					ft_error("Bad formatage1");
			}
			else
				champ(g, j, i);
			j++;
		}
		if (g->champ[i]->champ_size + TO_CHAMP != g->champ[i]->size)
			ft_error("Bad formatage2");
		i++;
	}
}
