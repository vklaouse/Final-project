/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_onscreen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 11:00:03 by semartin          #+#    #+#             */
/*   Updated: 2016/06/09 11:00:03 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	print_winner : Print the played that won
**	---------------------------------------------------------------------------
**	print_CDT : Print when ever cycle to die change
*/

void		ft_print_winner(t_glob *g)
{
	int i;
	int n;
	int cmp;

	i = 0;
	n = 0;
	cmp = 4;
	while (i < g->nb_champ)
	{
		if (n <= g->champ[i]->last_live)
		{
			n = g->champ[i]->last_live;
			cmp = i + 1;
		}
		i++;
	}
	ft_putstr("The Player ");
	ft_putnbr(cmp);
	ft_putstr(", \"");
	ft_putstr(g->champ[cmp - 1]->name);
	ft_putendl("\", has won !");
}

void		ft_print_cycle_to_die(t_glob *g)
{
	char	*s;
	char	*tmp;

	if (!(s = malloc(sizeof(*s) * 32)))
		ft_error("Allocation Error : Insufficient memory");
	tmp = s;
	ft_strcpy(tmp, "Cycle to die is now ");
	ft_itoa_cpy(g->prog->cycle_to_die, (tmp += 20));
	ft_strcpy((tmp += ft_strlen(tmp)), "\n");
	ft_buffer_screen(s, 0);
	free(s);
}
