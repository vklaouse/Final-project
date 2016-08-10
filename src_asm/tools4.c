/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 13:10:46 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/10 16:43:20 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

int		empty_line(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		nb_number(int n)
{
	int		i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_cjoin(char *s1, char *s2)
{
	char	*stock;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	stock = ft_strjoin(s1, s2);
	if (s1)
		ft_strdel(&s1);
	if (s2)
		ft_strdel(&s2);
	return (stock);
}

char	*ft_str_join_char(char *str, char c)
{
	int		i;
	char	*dest;

	if ((dest = (char*)malloc(sizeof(char) * ft_strlen(str) + 1))
		== NULL)
		ft_exit("Malloc Failure");
	i = 0;
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = c;
	dest[i + 1] = '\0';
	ft_strdel(&str);
	return (dest);
}

int		ft_strnchr(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}
