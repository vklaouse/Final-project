/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputzolu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 16:10:32 by aputzolu          #+#    #+#             */
/*   Updated: 2016/06/10 16:10:49 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"
#include "fcntl.h"

static char		**ret_strsplit(char const *s, char c, char **str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (*s)
	{
		j = 0;
		while (*s && *s == c)
			s++;
		if (*s != c && *s)
		{
			while (*s != c && *s)
			{
				str[i][j] = *s;
				s++;
				j++;
			}
			str[i][j] = '\0';
		}
		i++;
		while (*s && *s == c)
			s++;
	}
	str[i] = NULL;
	return (str);
}

static size_t	ft_wcount(char const *s, char c)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			while (*s != c && *s)
				s++;
			i++;
		}
	}
	return (i);
}

static size_t	ft_wlen(char const *s, char c, size_t index)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (s == NULL)
		return (0);
	while (i <= index)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		i++;
	}
	return (len);
}

char			**ft_strsplit2(char const *s, char c)
{
	char	**str;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((str = (char **)malloc(sizeof(*str) * (ft_wcount(s, c) + 1))) == NULL)
		ft_exit("Malloc Failure");
	if (str == NULL)
		return (NULL);
	while (i < ft_wcount(s, c))
	{
		if ((str[i] = (char *)malloc(sizeof(*s) * (ft_wlen(s, c, i) + 1)))
				== NULL)
			ft_exit("Malloc Failure");
		if (str[i] == NULL)
			return (NULL);
		i++;
	}
	str[i] = NULL;
	return (ret_strsplit(s, c, str));
}
