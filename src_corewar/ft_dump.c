/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 16:33:25 by semartin          #+#    #+#             */
/*   Updated: 2016/05/28 16:33:26 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	Dump the memory after n cycle if -dump is present, then stop the VM
*/

void	ft_dump(t_glob *g)
{
	int		i;
	char	*str;

	i = 0;
	while (i < MEM_SIZE)
	{
		str = ft_itoa_base_unsigned((int)g->arena[i], 16);
		if (ft_strlen(str) == 1)
		{
			ft_putchar('0');
			ft_putchar(*str);
		}
		else
			ft_putstr(str);
		if ((i + 1) % 32 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
		i++;
	}
	exit(0);
}
