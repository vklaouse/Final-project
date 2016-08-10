/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 09:54:46 by jschotte          #+#    #+#             */
/*   Updated: 2016/06/02 17:34:52 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
** __MAIN__ : Glob_init --> Initilise t_glob
**				ft_parsing : Parse Champ
**				ft_fill_map : Fill the arena with champs
**				ft_corewar : Make the VM and call the instr
*/

int	main(int ac, char **av)
{
	t_glob	*g;

	g = ft_glob_init(ac - 1, &(av[1]));
	ft_parsing(g);
	ft_fill_map(g);
	ft_corewar(g);
	return (0);
}
