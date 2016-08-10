/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 15:27:01 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/14 15:27:17 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

int		bad_n_c(char *s)
{
	char	*tmp;
	char	*tmp2;

	if (nb_char(s, '"') == 1 || empty_line(s))
		return (0);
	while (ft_isspace(*s))
		s++;
	tmp = ft_strsub(s, 0, 5);
	tmp2 = ft_strsub(s, 0, 8);
	if (tmp == NULL || tmp2 == NULL || (ft_strcmp(tmp, ".name")
		&& ft_strcmp(tmp2, ".comment")))
		return (1);
	return (0);
}
