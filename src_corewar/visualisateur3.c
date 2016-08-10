/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisateur3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 14:52:01 by vklaouse          #+#    #+#             */
/*   Updated: 2016/05/30 15:48:20 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		ft_color(t_glob *g, int z)
{
	if (g->color[z] == 1)
		return (0xFF0000);
	else if (g->color[z] == 2)
		return (0xFFFFFF);
	else if (g->color[z] == 3)
		return (0x0000FF);
	else if (g->color[z] == 4)
		return (0x00FF00);
	else
		return (0x808080);
}

int		key_hook(int keycode, t_env *e)
{
	if (keycode == ESCAP)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(0);
	}
	return (0);
}

void	draw_black_2(t_glob *g)
{
	int	i;
	int	x;

	i = 0;
	while (i < 100)
	{
		x = 0;
		while (x < 340)
		{
			ft_pixel_put_image(g->e->img[1], x, i, 0x000000);
			x++;
		}
		i++;
	}
}

void	draw_black_3(t_glob *g, int color, int nb_img)
{
	int	i;
	int	x;

	i = 0;
	while (i < 19)
	{
		x = 0;
		while (x < 29)
		{
			ft_pixel_put_image(g->e->img[nb_img], x, i, color);
			x++;
		}
		i++;
	}
}
