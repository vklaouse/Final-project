/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:50:01 by semartin          #+#    #+#             */
/*   Updated: 2016/05/19 11:50:01 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	byte_into_long : Turn a 8 bytes tab into an long (64bit system)
**	---------------------------------------------------------------------------
** 	byte_into_int : Turn a 4 bytes tab into an into (64bit system)
**	---------------------------------------------------------------------------
** 	byte_into_short : Turn a 2 bytes tab into a short (64bit system)
**						Care, might segfault if tab isn't well defined !
**						--> Do not check if the tab is defined !!
**	---------------------------------------------------------------------------
** 	clear_byte : Fill the byte tab with 0 (until the next byte is a 0)
**	---------------------------------------------------------------------------
**	reg_cpy : Cpy the 16 reg of one process into an nother register tab
*/

long	byte_into_long(t_byte *tab)
{
	long	nb;
	int		i;

	i = 0;
	nb = 0;
	if (tab)
	{
		while (i < 8)
		{
			nb = nb * 256 + tab[i];
			i++;
		}
		return (nb);
	}
	ft_error("Error in byte_into_long");
	return (0);
}

int		byte_into_int(t_byte *tab)
{
	int nb;
	int i;

	i = 0;
	nb = 0;
	if (tab)
	{
		while (i < 4)
		{
			nb = nb * 256 + tab[i];
			i++;
		}
		return (nb);
	}
	ft_error("Error in byte_into_int");
	return (0);
}

short	byte_into_short(t_byte *tab)
{
	short	nb;
	int		i;

	i = 0;
	if (tab)
	{
		while (i < 2)
		{
			nb = nb * 256 + tab[i];
			i++;
		}
		return (nb);
	}
	ft_error("Error in byte_into_short");
	return (0);
}

void	clear_byte(t_byte *tab)
{
	int i;

	i = 0;
	while (tab[i] && i < 16)
		tab[i++] = 0;
}

void	reg_cpy(int *r1, int *r2)
{
	int i;

	i = 0;
	while (i < 16)
	{
		r2[i] = r1[i];
		i++;
	}
}
