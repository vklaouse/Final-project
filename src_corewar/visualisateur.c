/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisateur.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 18:01:31 by vklaouse          #+#    #+#             */
/*   Updated: 2016/05/30 18:17:10 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void	processus_img_2(t_glob *g)
{
	if (!(g->e->img[5] = malloc(sizeof(t_img))))
		ft_error("Allocation Error : Insufficient memory");
	g->e->img[5]->adr = mlx_new_image(g->e->mlx, 29, 19);
	g->e->img[5]->e = g->e;
	g->e->img[5]->endian = 1;
	if (!(g->e->img[3]->data = malloc(sizeof(char*))))
		ft_error("Allocation Error : Insufficient memory");
	g->e->img[5]->data = mlx_get_data_addr(g->e->img[5]->adr,
	&(g->e->img[5]->bpp), &(g->e->img[5]->size_line), &g->e->img[5]->endian);
	draw_black_3(g, 0x0000FF, 5);
	if (g->nb_champ > 3)
	{
		if (!(g->e->img[6] = malloc(sizeof(t_img))))
			ft_error("Allocation Error : Insufficient memory");
		g->e->img[6]->adr = mlx_new_image(g->e->mlx, 29, 19);
		g->e->img[6]->e = g->e;
		g->e->img[6]->endian = 1;
		if (!(g->e->img[6]->data = malloc(sizeof(char*))))
			ft_error("Allocation Error : Insufficient memory");
		g->e->img[6]->data = mlx_get_data_addr(g->e->img[6]->adr,
		&(g->e->img[6]->bpp), &(g->e->img[6]->size_line),
		&g->e->img[6]->endian);
		draw_black_3(g, 0x00FF00, 6);
	}
}

static void	processus_img(t_glob *g)
{
	if (!(g->e->img[3] = malloc(sizeof(t_img))))
		ft_error("Allocation Error : Insufficient memory");
	g->e->img[3]->adr = mlx_new_image(g->e->mlx, 29, 19);
	g->e->img[3]->e = g->e;
	g->e->img[3]->endian = 1;
	if (!(g->e->img[3]->data = malloc(sizeof(char*))))
		ft_error("Allocation Error : Insufficient memory");
	g->e->img[3]->data = mlx_get_data_addr(g->e->img[3]->adr,
	&(g->e->img[3]->bpp), &(g->e->img[3]->size_line), &g->e->img[3]->endian);
	draw_black_3(g, 0xFF0000, 3);
	if (g->nb_champ > 1)
	{
		if (!(g->e->img[4] = malloc(sizeof(t_img))))
			ft_error("Allocation Error : Insufficient memory");
		g->e->img[4]->adr = mlx_new_image(g->e->mlx, 29, 19);
		g->e->img[4]->e = g->e;
		g->e->img[4]->endian = 1;
		if (!(g->e->img[4]->data = malloc(sizeof(char*))))
			ft_error("Allocation Error : Insufficient memory");
		g->e->img[4]->data = mlx_get_data_addr(g->e->img[4]->adr, &(
		g->e->img[4]->bpp), &(g->e->img[4]->size_line), &g->e->img[4]->endian);
		draw_black_3(g, 0xFFFFFF, 4);
	}
	if (g->nb_champ > 2)
		processus_img_2(g);
}

static void	create_img_modif(t_glob *g)
{
	mlx_put_image_to_window(g->e->mlx, g->e->win, g->e->img[0]->adr, 0, 0);
	if (!(g->e->img[1] = malloc(sizeof(t_img))))
		ft_error("Allocation Error : Insufficient memory");
	g->e->img[1]->adr = mlx_new_image(g->e->mlx, 100, 340);
	g->e->img[1]->e = g->e;
	g->e->img[1]->endian = 1;
	if (!(g->e->img[1]->data = malloc(sizeof(char*))))
		ft_error("Allocation Error : Insufficient memory");
	g->e->img[1]->data = mlx_get_data_addr(g->e->img[1]->adr,
	&(g->e->img[1]->bpp), &(g->e->img[1]->size_line), &g->e->img[1]->endian);
	draw_black_2(g);
	if (!(g->e->img[2] = malloc(sizeof(t_img))))
		ft_error("Allocation Error : Insufficient memory");
	g->e->img[2]->adr = mlx_new_image(g->e->mlx, 29, 19);
	g->e->img[2]->e = g->e;
	g->e->img[2]->endian = 1;
	if (!(g->e->img[2]->data = malloc(sizeof(char*))))
		ft_error("Allocation Error : Insufficient memory");
	g->e->img[2]->data = mlx_get_data_addr(g->e->img[2]->adr,
	&(g->e->img[2]->bpp), &(g->e->img[2]->size_line), &g->e->img[2]->endian);
	draw_black_3(g, 0x000000, 2);
	processus_img(g);
}

static void	create_img(t_glob *g)
{
	g->e->mlx = mlx_init();
	g->e->win = mlx_new_window(g->e->mlx, LENGTH, WIDTH, "Arena");
	if (!(g->e->img = malloc(sizeof(t_img *) * 7)))
		ft_error("Allocation Error : Insufficient memory");
	if (!(g->e->img[0] = malloc(sizeof(t_img))))
		ft_error("Allocation Error : Insufficient memory");
	g->e->img[0]->adr = mlx_new_image(g->e->mlx, LENGTH, WIDTH);
	g->e->img[0]->e = g->e;
	g->e->img[0]->endian = 1;
	if (!(g->e->img[0]->data = malloc(sizeof(char*))))
		ft_error("Allocation Error : Insufficient memory");
	g->e->img[0]->data = mlx_get_data_addr(g->e->img[0]->adr,
	&(g->e->img[0]->bpp), &(g->e->img[0]->size_line), &g->e->img[0]->endian);
	draw(g);
	create_img_modif(g);
	aff_arena(g);
}

int			visualisateur(t_glob *g)
{
	t_env *e;

	if (!(e = malloc(sizeof(*e))))
		ft_error("Allocation Error : Insufficient memory");
	if (MEM_SIZE != 4096)
		ft_error("Error");
	g->e = e;
	create_img(g);
	return (0);
}
