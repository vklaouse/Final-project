/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 17:57:28 by semartin          #+#    #+#             */
/*   Updated: 2016/05/09 19:17:00 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_error : Print the error on stderr and then exit the program
**	---------------------------------------------------------------------------
**	ft_chanp_right : Check if the -n before a champ is right or not
**					--> Call ft_error if not
*/

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(0);
}

void	ft_champ_right(t_glob *g)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		if (g->number_champ[i] > g->nb_champ)
			ft_error("Error : Champion number too high");
		j = i + 1;
		while (j < 4)
		{
			if (g->number_champ[i] == g->number_champ[j]
					&& g->number_champ[i] != 0)
				ft_error("Error : Two champions has the same number");
			j++;
		}
		i++;
	}
}
