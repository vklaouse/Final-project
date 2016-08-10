/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisateur2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 14:45:49 by vklaouse          #+#    #+#             */
/*   Updated: 2016/05/27 15:41:28 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void	line(t_glob *g)
{
	t_ligne	l;

	l.dx = ft_abs(g->e->x_1 - g->e->x_0);
	l.sx = g->e->x_0 < g->e->x_1 ? 1 : -1;
	l.dy = ft_abs(g->e->y_1 - g->e->y_0);
	l.sy = g->e->y_0 < g->e->y_1 ? 1 : -1;
	l.err = (l.dx > l.dy ? l.dx : -l.dy) / 2;
	while (1)
	{
		ft_pixel_put_image(g->e->img[0], g->e->x_0, g->e->y_0, 0x808080);
		if (g->e->x_0 == g->e->x_1 && g->e->y_0 == g->e->y_1)
			break ;
		l.e2 = l.err;
		if (l.e2 > -l.dx)
		{
			l.err -= l.dy;
			g->e->x_0 += l.sx;
		}
		if (l.e2 < l.dy)
		{
			l.err += l.dx;
			g->e->y_0 += l.sy;
		}
	}
}

int			draw(t_glob *g)
{
	int	i;

	i = 0;
	g->e->y_0 = 40;
	while (i <= 64)
	{
		g->e->x_0 = 30;
		g->e->y_1 = g->e->y_0;
		g->e->x_1 = 30 + 1920;
		line(g);
		g->e->y_0 += 20;
		i++;
	}
	i = 0;
	g->e->x_0 = 30;
	while (i <= 64)
	{
		g->e->y_0 = 40;
		g->e->x_1 = g->e->x_0;
		g->e->y_1 = 40 + 1280;
		line(g);
		g->e->x_0 += 30;
		i++;
	}
	return (0);
}

static void	aff(int i, t_glob *g, char *s)
{
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
}

static void	aff_legend(t_glob *g)
{
	mlx_string_put(g->e->mlx, g->e->win, 2000, 100, W, "CYCLE : ");
	mlx_string_put(g->e->mlx, g->e->win, 2000, 120, W, "CYCLE TO DIE : ");
	mlx_string_put(g->e->mlx, g->e->win, 2000, 140, W, "ALL CYCLE : ");
	mlx_string_put(g->e->mlx, g->e->win, 2000, 160, W, "CHECK : ");
	mlx_string_put(g->e->mlx, g->e->win, 2000, 180, W, "PROCESSUS : ");
	if (g->nb_champ > 0)
	{
		mlx_string_put(g->e->mlx, g->e->win, 2000, 200, W, "CHAMP 1 NB : ");
		mlx_string_put(g->e->mlx, g->e->win, 2000, 220, W, "CHAMP 1 LAST : ");
	}
	if (g->nb_champ > 1)
	{
		mlx_string_put(g->e->mlx, g->e->win, 2000, 240, W, "CHAMP 2 NB : ");
		mlx_string_put(g->e->mlx, g->e->win, 2000, 260, W, "CHAMP 2 LAST : ");
	}
	if (g->nb_champ > 2)
	{
		mlx_string_put(g->e->mlx, g->e->win, 2000, 280, W, "CHAMP 3 NB : ");
		mlx_string_put(g->e->mlx, g->e->win, 2000, 300, W, "CHAMP 3 LAST : ");
	}
	if (g->nb_champ > 3)
	{
		mlx_string_put(g->e->mlx, g->e->win, 2000, 320, W, "CHAMP 4 NB : ");
		mlx_string_put(g->e->mlx, g->e->win, 2000, 340, W, "CHAMP 4 LAST : ");
	}
}

void		aff_arena(t_glob *g)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	g->e->x_0 = 30;
	g->e->y_0 = 40;
	j = 0;
	while (i < MEM_SIZE)
	{
		if (j == 64)
		{
			g->e->x_0 = 30;
			g->e->y_0 += 20;
			j = 0;
		}
		s = ft_itoa_base_unsigned(g->arena[i], 16);
		aff(i, g, s);
		g->e->x_0 += 30;
		i++;
		j++;
		free(s);
	}
	aff_legend(g);
}
