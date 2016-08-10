/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_processus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 18:32:03 by vklaouse          #+#    #+#             */
/*   Updated: 2016/05/30 18:49:21 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void	process_write(t_glob *g, int player, t_proc *p, char *s)
{
	p->old_pc = p->pc;
	mlx_put_image_to_window(g->e->mlx, g->e->win, g->e->img[player]->adr,
							g->e->x_0 + 1, g->e->y_0 + 1);
	s = ft_itoa_base_unsigned(g->arena[p->pc], 16);
	if (ft_strlen(s) == 1)
	{
		mlx_string_put(g->e->mlx, g->e->win, g->e->x_0 + 6, g->e->y_0 + 15,
					0x000000, "0");
		mlx_string_put(g->e->mlx, g->e->win, g->e->x_0 + 16, g->e->y_0 + 15,
					0x000000, s);
	}
	else
		mlx_string_put(g->e->mlx, g->e->win, g->e->x_0 + 6, g->e->y_0 + 15,
					0x000000, s);
	free(s);
}

static void	write_process(t_glob *g, int player, t_proc *p)
{
	char *s;

	s = NULL;
	if (p->old_pc != -1)
	{
		g->e->y_1 = (p->old_pc / 64) * 20 + 40;
		g->e->x_1 = (p->old_pc % 64) * 30 + 30;
		mlx_put_image_to_window(g->e->mlx, g->e->win, g->e->img[2]->adr,
								g->e->x_1 + 1, g->e->y_1 + 1);
		s = ft_itoa_base_unsigned(g->arena[p->old_pc], 16);
		if (ft_strlen(s) == 1)
		{
			mlx_string_put(g->e->mlx, g->e->win, g->e->x_1 + 6, g->e->y_1 + 15,
						ft_color(g, p->old_pc), "0");
			mlx_string_put(g->e->mlx, g->e->win, g->e->x_1 + 16, g->e->y_1 + 15,
						ft_color(g, p->old_pc), s);
		}
		else
			mlx_string_put(g->e->mlx, g->e->win, g->e->x_1 + 6, g->e->y_1 + 15,
						ft_color(g, p->old_pc), s);
	}
	process_write(g, player, p, s);
}

void		ft_process(t_glob *g)
{
	t_list	*tmp;
	t_proc	*p;
	int		player;

	tmp = g->begin_lst;
	while (tmp != NULL)
	{
		p = tmp->content;
		p->pc %= MEM_SIZE;
		p->old_pc %= MEM_SIZE;
		if (p->player == -1)
			player = 3;
		else if (p->player == -2)
			player = 4;
		else if (p->player == -3)
			player = 5;
		else if (p->player == -4)
			player = 6;
		g->e->y_0 = (p->pc / 64) * 20 + 40;
		g->e->x_0 = (p->pc % 64) * 30 + 30;
		if (p->old_pc != p->pc)
			write_process(g, player, p);
		tmp = tmp->next;
	}
}
