/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 17:46:39 by vklaouse          #+#    #+#             */
/*   Updated: 2016/06/05 18:12:06 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void	modif_legend_again(t_glob *g)
{
	char *s;

	s = ft_itoa(g->champ[0]->nb_live);
	mlx_string_put(g->e->mlx, g->e->win, 2100, 200, W, s);
	free(s);
	s = ft_itoa(g->champ[0]->last_live);
	mlx_string_put(g->e->mlx, g->e->win, 2100, 220, W, s);
	free(s);
	if (g->nb_champ > 1)
	{
		s = ft_itoa(g->champ[1]->nb_live);
		mlx_string_put(g->e->mlx, g->e->win, 2100, 240, W, s);
		free(s);
		s = ft_itoa(g->champ[1]->last_live);
		mlx_string_put(g->e->mlx, g->e->win, 2100, 260, W, s);
		free(s);
	}
}

static void	modif_leg(t_glob *g)
{
	char *s;

	s = ft_itoa(g->prog->cycle);
	mlx_string_put(g->e->mlx, g->e->win, 2100, 100, W, s);
	free(s);
	s = ft_itoa(g->prog->cycle_to_die);
	mlx_string_put(g->e->mlx, g->e->win, 2100, 120, W, s);
	free(s);
	s = ft_itoa(g->prog->all_cycle);
	mlx_string_put(g->e->mlx, g->e->win, 2100, 140, W, s);
	free(s);
	s = ft_itoa(g->prog->check);
	mlx_string_put(g->e->mlx, g->e->win, 2100, 160, W, s);
	free(s);
	s = ft_itoa(g->prog->nb_proc);
	mlx_string_put(g->e->mlx, g->e->win, 2100, 180, W, s);
	free(s);
	modif_legend_again(g);
}

void		modif_legend(t_glob *g)
{
	char *s;

	mlx_put_image_to_window(g->e->mlx, g->e->win, g->e->img[1]->adr, 2100, 80);
	modif_leg(g);
	if (g->nb_champ > 2)
	{
		s = ft_itoa(g->champ[2]->nb_live);
		mlx_string_put(g->e->mlx, g->e->win, 2100, 280, W, s);
		free(s);
		s = ft_itoa(g->champ[2]->last_live);
		mlx_string_put(g->e->mlx, g->e->win, 2100, 300, W, s);
		free(s);
	}
	if (g->nb_champ > 3)
	{
		s = ft_itoa(g->champ[3]->nb_live);
		mlx_string_put(g->e->mlx, g->e->win, 2100, 320, W, s);
		free(s);
		s = ft_itoa(g->champ[3]->last_live);
		mlx_string_put(g->e->mlx, g->e->win, 2100, 340, W, s);
		free(s);
	}
}

static void	modif_case(t_glob *g, int i)
{
	char	*s;

	mlx_put_image_to_window(g->e->mlx, g->e->win, g->e->img[2]->adr,
							g->e->x_0 + 1, g->e->y_0 + 1);
	s = ft_itoa_base_unsigned(g->arena[i], 16);
	if (ft_strlen(s) == 1)
	{
		mlx_string_put(g->e->mlx, g->e->win, g->e->x_0 + 6, g->e->y_0 + 15,
					ft_color(g, i), "0");
		mlx_string_put(g->e->mlx, g->e->win, g->e->x_0 + 16, g->e->y_0 + 15,
					ft_color(g, i), s);
	}
	else
		mlx_string_put(g->e->mlx, g->e->win, g->e->x_0 + 6, g->e->y_0 + 15,
					ft_color(g, i), s);
	free(s);
}

void		modif_arena(t_glob *g, int z)
{
	int	i;
	int	j;

	i = 0;
	g->e->x_0 = 30;
	g->e->y_0 = 40;
	j = 0;
	while (i <= z)
	{
		if (j == 64)
		{
			g->e->x_0 = 30;
			g->e->y_0 += 20;
			j = 0;
		}
		if (i == z)
			modif_case(g, i);
		g->e->x_0 += 30;
		i++;
		j++;
	}
}
