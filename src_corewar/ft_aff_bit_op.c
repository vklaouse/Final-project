/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff_bit_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 15:30:17 by semartin          #+#    #+#             */
/*   Updated: 2016/06/08 15:30:20 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_print_X : If -op : Print the operation
*/

void	ft_print_add(t_proc *p)
{
	int		i;
	int		nb;
	char	*s;
	char	*tmp;

	if (!(s = malloc(sizeof(*s) * 64)))
		ft_error("Allocation Error : Insufficient memory");
	tmp = s;
	i = 0;
	nb = number_digit(p->number);
	ft_strcpy(tmp++, "P");
	while (i++ < 5 - nb)
		ft_strcpy(tmp++, " ");
	ft_itoa_cpy(p->number, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | add r");
	ft_itoa_cpy(p->instr[2], (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " r");
	ft_itoa_cpy(p->instr[3], (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " r");
	ft_itoa_cpy(p->instr[4], (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp += ft_strlen(tmp)), "\n");
	ft_buffer_screen(s, 0);
	free(s);
}

void	ft_print_sub(t_proc *p)
{
	int		i;
	int		nb;
	char	*s;
	char	*tmp;

	if (!(s = malloc(sizeof(*s) * 64)))
		ft_error("Allocation Error : Insufficient memory");
	tmp = s;
	i = 0;
	nb = number_digit(p->number);
	ft_strcpy(tmp++, "P");
	while (i++ < 5 - nb)
		ft_strcpy(tmp++, " ");
	ft_itoa_cpy(p->number, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | sub r");
	ft_itoa_cpy(p->instr[2], (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " r");
	ft_itoa_cpy(p->instr[3], (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " r");
	ft_itoa_cpy(p->instr[4], (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp += ft_strlen(tmp)), "\n");
	ft_buffer_screen(s, 0);
	free(s);
}

void	ft_print_and(t_proc *p, int p1, int p2)
{
	int		i;
	int		nb;
	char	*s;
	char	*tmp;

	if (!(s = malloc(sizeof(*s) * 64)))
		ft_error("Allocation Error : Insufficient memory");
	tmp = s;
	i = 0;
	nb = number_digit(p->number);
	ft_strcpy(tmp++, "P");
	while (i++ < 5 - nb)
		ft_strcpy(tmp++, " ");
	ft_itoa_cpy(p->number, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | and ");
	ft_itoa_cpy(p1, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " ");
	ft_itoa_cpy(p2, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " r");
	ft_itoa_cpy(p->instr[2 + p->code[0]
				+ p->code[1]], (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp += ft_strlen(tmp)), "\n");
	ft_buffer_screen(s, 0);
	free(s);
}

void	ft_print_or(t_proc *p, int p1, int p2)
{
	int		i;
	int		nb;
	char	*s;
	char	*tmp;

	if (!(s = malloc(sizeof(*s) * 64)))
		ft_error("Allocation Error : Insufficient memory");
	tmp = s;
	i = 0;
	nb = number_digit(p->number);
	ft_strcpy(tmp++, "P");
	while (i++ < 5 - nb)
		ft_strcpy(tmp++, " ");
	ft_itoa_cpy(p->number, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | or ");
	ft_itoa_cpy(p1, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " ");
	ft_itoa_cpy(p2, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " r");
	ft_itoa_cpy(p->instr[2 + p->code[0]
				+ p->code[1]], (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp += ft_strlen(tmp)), "\n");
	ft_buffer_screen(s, 0);
	free(s);
}

void	ft_print_xor(t_proc *p, int p1, int p2)
{
	int		i;
	int		nb;
	char	*s;
	char	*tmp;

	if (!(s = malloc(sizeof(*s) * 64)))
		ft_error("Allocation Error : Insufficient memory");
	tmp = s;
	i = 0;
	nb = number_digit(p->number);
	ft_strcpy(tmp++, "P");
	while (i++ < 5 - nb)
		ft_strcpy(tmp++, " ");
	ft_itoa_cpy(p->number, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | xor ");
	ft_itoa_cpy(p1, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " ");
	ft_itoa_cpy(p2, (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " r");
	ft_itoa_cpy(p->instr[2 + p->code[0]
				+ p->code[1]], (tmp = tmp + ft_strlen(tmp)));
	ft_strcpy((tmp += ft_strlen(tmp)), "\n");
	ft_buffer_screen(s, 0);
	free(s);
}
