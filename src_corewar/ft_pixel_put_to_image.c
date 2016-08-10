/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_put_to_image.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <semartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 12:50:34 by semartin          #+#    #+#             */
/*   Updated: 2015/09/17 13:18:04 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** ft_pixel_put_image : Put a pixel of the color on the image
*/

void	ft_pixel_put_image(t_img *img, int x, int y, int color)
{
	unsigned int pos;
	unsigned int mem;

	if (x >= 0 && x <= LENGTH && y >= 0 && y <= WIDTH)
	{
		pos = (y * img->size_line) + ((img->bpp / 8) * x);
		mem = mlx_get_color_value(img->e->mlx, color);
		img->data[pos + 0] = (mem & 0xFF);
		img->data[pos + 1] = (mem & 0xFF00) >> 8;
		img->data[pos + 2] = (mem & 0xFF0000) >> 16;
	}
}
