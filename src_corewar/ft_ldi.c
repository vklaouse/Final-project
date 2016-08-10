/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 10:51:01 by semartin          #+#    #+#             */
/*   Updated: 2016/06/06 10:51:03 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_ldi_show_op : commun part of ldi and lldi if option -op
**	---------------------------------------------------------------------------
**	flag_ldi/lldi : If option -op : Add the operation to the buffer
**					that will be printed on screen
**	---------------------------------------------------------------------------
** 	ft_ldi : Sum x and y. Use it as an adress. Search the value at this adress
**				Put this value into r.
**				Calcul x and y with a modulo IDX_MOD
**	---------------------------------------------------------------------------
** 	ft_lldi : Same than ldi exept the modulo
**				If (r != 0) change the carry to 1
*/

static void	ldi_show_op(int n1, int n2, int n, char *tmp)
{
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), "\n       | -> load from ");
	ft_itoa_cpy(n1, (tmp += 23));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " + ");
	ft_itoa_cpy(n2, (tmp += 3));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " = ");
	ft_itoa_cpy(n1 + n2, (tmp += 3));
	if (n == 0)
		ft_strcpy((tmp = tmp + ft_strlen(tmp)), " (with pc and mod ");
	else if (n == 1)
		ft_strcpy((tmp = tmp + ft_strlen(tmp)), " (with pc ");
}

void		flag_ldi(t_proc *p, int n1, int n2, int r)
{
	int		i;
	int		nb;
	char	*s;
	char	*tmp;

	if (!(s = malloc(sizeof(*s) * 128)))
		ft_error("Allocation Error : Insufficient memory");
	tmp = s;
	i = 0;
	nb = number_digit(p->number);
	ft_strcpy(tmp++, "P");
	while (i++ < 5 - nb)
		ft_strcpy(tmp++, " ");
	ft_itoa_cpy(p->number, tmp);
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | ldi ");
	ft_itoa_cpy(n1, (tmp += 7));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " ");
	ft_itoa_cpy(n2, ++tmp);
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " r");
	ft_itoa_cpy(r, (tmp += 2));
	ldi_show_op(n1, n2, 0, tmp);
	ft_itoa_cpy(p->pc + (n1 + n2) % IDX_MOD, (tmp += ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), ")\n");
	ft_buffer_screen(s, 0);
	free(s);
}

void		flag_lldi(t_proc *p, int n1, int n2, int r)
{
	int		i;
	int		nb;
	char	*s;
	char	*tmp;

	if (!(s = malloc(sizeof(*s) * 128)))
		ft_error("Allocation Error : Insufficient memory");
	tmp = s;
	i = 0;
	nb = number_digit(p->number);
	ft_strcpy(tmp++, "P");
	while (i++ < 5 - nb)
		ft_strcpy(tmp++, " ");
	ft_itoa_cpy(p->number, (tmp += ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | lldi ");
	ft_itoa_cpy(n1, (tmp += 8));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " ");
	ft_itoa_cpy(n2, ++tmp);
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " r");
	ft_itoa_cpy(r, (tmp += 2));
	ldi_show_op(n1, n2, 0, tmp);
	ft_itoa_cpy(p->pc + (n1 + n2), (tmp += ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), "\n");
	ft_buffer_screen(s, 0);
	free(s);
}

void		ft_ldi(int nb, int *r, t_glob *g, t_proc *p)
{
	int cmp;

	cmp = p->pc + (nb % IDX_MOD);
	*r = byte_into_int(&(g->arena[cmp]));
}

void		ft_lldi(int nb, int *r, t_glob *g, t_proc *p)
{
	int cmp;

	cmp = p->pc + nb;
	*r = byte_into_int(&(g->arena[cmp]));
	if (*r == 0)
		p->carry = 0;
	else
		p->carry = 1;
}
