/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:25:03 by semartin          #+#    #+#             */
/*   Updated: 2016/06/05 17:25:04 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_buffer_screen : Buffer that stoc everything that will be written
**	---------------------------------------------------------------------------
**	ft_print_pc : Print the pc modification
**	---------------------------------------------------------------------------
**	ft_print_cycle_to_die : Print when ever it's cycle_to_die
*/

static void	print_buffer(char *s)
{
	if (s)
	{
		ft_putstr(s);
		free(s);
	}
}

void		ft_buffer_screen(char *str, int n)
{
	static char	*s = NULL;
	static int	i = 0;
	int			j;

	if (n == 1)
	{
		print_buffer(s);
		return ;
	}
	if (s == NULL)
		s = malloc(sizeof(*s) * 65536);
	j = 0;
	while (str[j] && i <= 65534)
	{
		s[i] = str[j];
		i++;
		j++;
	}
	s[i] = '\0';
	if (i == 65535)
	{
		ft_putstr(s);
		i = 0;
		ft_buffer_screen(&str[j], 0);
	}
}

static void	ft_print_3(t_glob *g, t_proc *p, int size, char *tmp)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_itoa_base_cpy(g->arena[(p->pc + i) % MEM_SIZE], 16, tmp);
		if (ft_strlen(tmp) == 1)
		{
			*(tmp + 2) = '\0';
			*(tmp + 1) = *tmp;
			*tmp = '0';
		}
		ft_strcpy(tmp + 2, " ");
		tmp += ft_strlen(tmp);
		i++;
	}
	ft_strcpy(tmp, "\n");
}

static void	ft_print_2(t_glob *g, t_proc *p, int size, char *tmp)
{
	char *s1;

	s1 = ft_itoa_base_small(p->pc + size, 16);
	if (ft_strlen(s1) == 1)
		ft_strcpy((tmp += 6), "000");
	else if (ft_strlen(s1) == 2)
		ft_strcpy((tmp += 6), "00");
	else if (ft_strlen(s1) == 3)
		ft_strcpy((tmp += 6), "0");
	ft_strcpy((tmp += ft_strlen(tmp)), s1);
	free(s1);
	ft_strcpy((tmp += ft_strlen(tmp)), ") ");
	tmp += ft_strlen(tmp);
	ft_print_3(g, p, size, tmp);
}

void		ft_print_pc(t_glob *g, t_proc *p, int size)
{
	char *s;
	char *s1;
	char *tmp;

	p->pc = p->pc % MEM_SIZE;
	s = malloc(sizeof(*s) * 128);
	tmp = s;
	ft_strcpy(tmp, "ADV ");
	ft_itoa_cpy(size, (tmp += 4));
	ft_strcpy((tmp += ft_strlen(tmp)), " (0x");
	s1 = ft_itoa_base_small(p->pc, 16);
	if (ft_strlen(s1) == 1)
		ft_strcpy((tmp += 4), "000");
	else if (ft_strlen(s1) == 2)
		ft_strcpy((tmp += 4), "00");
	else if (ft_strlen(s1) == 3)
		ft_strcpy((tmp += 4), "0");
	ft_strcpy((tmp += ft_strlen(tmp)), s1);
	free(s1);
	ft_strcpy((tmp += ft_strlen(tmp)), " -> 0x");
	ft_print_2(g, p, size, tmp);
	ft_buffer_screen(s, 0);
	free(s);
}
