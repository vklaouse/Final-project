/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 12:10:18 by semartin          #+#    #+#             */
/*   Updated: 2016/05/10 12:10:18 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
** 	fill_map : Fill the areana with 0 then call champ_into_map for every champ
**				Calcul the place where the champion will be written (start)
**	---------------------------------------------------------------------------
**	champ_into_map : Write the champion in the arena.
*/

static void	ft_champ_into_map(int n, int start, t_glob *g)
{
	int i;

	i = 0;
	while (i < g->champ[n]->champ_size)
	{
		if (i >= CHAMP_MAX_SIZE)
			ft_error("Champion too long");
		g->arena[start + i] = g->champ[n]->prog[i];
		g->color[start + i] = n + 1;
		i++;
	}
}

void		ft_fill_map(t_glob *g)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		g->arena[i] = 0;
		g->color[i++] = 0;
	}
	i = 0;
	while (i < g->nb_champ)
	{
		ft_champ_into_map(i, ((double)i / (double)g->nb_champ) * MEM_SIZE, g);
		i++;
	}
}
