/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnct2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 11:13:23 by semartin          #+#    #+#             */
/*   Updated: 2016/06/10 15:36:47 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
** 	ft_encode : Return an int[4] with the size needed for the instr
**	---------------------------------------------------------------------------
** 	ft_encode_space : calcul the size needed on the prog (On 3 bit)
**	---------------------------------------------------------------------------
**	ft_numver_digit : Return the number of digit if the int in param
**	---------------------------------------------------------------------------
**	ft_print_cycle : Print the cycle that we curently are on
**	---------------------------------------------------------------------------
**	ft_champ_order : Fill the tab with the order of every champ
**						(depending on -n)
*/

void	ft_encode(t_byte n, t_proc *p)
{
	int	i;
	int	nb;

	i = 3;
	while (i >= 0)
	{
		nb = n % 4;
		if (nb == 0)
			p->code[i] = 0;
		else if (nb == 1)
			p->code[i] = 1;
		else if (nb == 2)
			p->code[i] = 4;
		else
			p->code[i] = 2;
		n /= 4;
		i--;
	}
}

int		ft_encode_space(int *code)
{
	return (code[0] + code[1] + code[2]);
}

int		number_digit(int n)
{
	int i;

	i = 1;
	while ((n = n / 10))
		i++;
	return (i);
}

void	ft_print_cycle(t_glob *g)
{
	char	*s;
	char	*tmp;

	if (!(s = malloc(sizeof(*s) * 32)))
		ft_error("Allocation Error : Insufficient memory");
	tmp = s;
	ft_strcpy(tmp, "It is now cycle ");
	ft_itoa_cpy(g->prog->all_cycle, (tmp += 16));
	ft_strcpy((tmp += ft_strlen(tmp)), "\n");
	ft_buffer_screen(s, 0);
	free(s);
}

void	ft_champ_order(t_glob *g)
{
	int n;
	int i;
	int j;

	i = -1;
	n = 0;
	while (++i < g->nb_champ)
	{
		if (g->number_champ[i] == 0)
		{
			j = 0;
			while (j < g->nb_champ)
			{
				if (g->number_champ[j] == n + 1)
				{
					n = g->number_champ[j];
					j = 0;
					break ;
				}
				else
					j++;
			}
			g->number_champ[i] = ++n;
		}
	}
}
