/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 13:36:16 by jschotte          #+#    #+#             */
/*   Updated: 2016/06/13 14:47:48 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"

char	get_octet_code(t_par *params)
{
	char total;

	total = 0;
	if (params->p != NULL)
	{
		total += check_type_param(params, 6, 7);
		params = params->next;
		if (params->p != NULL)
		{
			total += check_type_param(params, 4, 5);
			params = params->next;
			if (params->p != NULL)
				total += check_type_param(params, 2, 3);
		}
	}
	return (total);
}

int		get_difflabel(t_label *label, char *str)
{
	t_label *tmp;

	tmp = label;
	while (ft_strcmp(tmp->name, str) != 0)
		tmp = tmp->next;
	return (tmp->sum);
}

int		ft_power(int n, int p)
{
	int	result;

	result = 1;
	if (p < 0)
		return (0);
	while (p > 0)
	{
		result *= n;
		p--;
	}
	return (result);
}

int		get_octet_code_int(t_par *params)
{
	int total;

	total = 0;
	if (params->p != NULL)
	{
		total += check_type_param_int(params, 6, 7);
		params = params->next;
		if (params->p != NULL)
		{
			total += check_type_param_int(params, 4, 5);
			params = params->next;
			if (params->p != NULL)
				total += check_type_param_int(params, 2, 3);
		}
	}
	return (total);
}

void	check_octetcode(int op, int oct)
{
	if ((op == 2 || op == 13) && (oct != 144 && oct != 208))
		ft_exit("Bad type params");
	else if ((op == 3) && (oct != 80 && oct != 112))
		ft_exit("Bad type params");
	else if ((op == 4 || op == 5) && (oct != 84))
		ft_exit("Bad type params");
	else if ((op == 16) && (oct != 64))
		ft_exit("Bad type params");
	else if ((op == 10 || op == 14) && (oct != 84 && oct != 100
		&& oct != 164 && oct != 148 && oct != 228 && oct != 212))
		ft_exit("Bad type params");
	else if ((op == 11) && (oct != 84 && oct != 88
		&& oct != 104 && oct != 100 && oct != 120 && oct != 116))
		ft_exit("Bad type params");
	else if ((op >= 6 && op <= 8) && (oct != 84 && oct != 116
		&& oct != 100 && oct != 212 && oct != 244 && oct != 228
		&& oct != 148 && oct != 180 && oct != 164))
		ft_exit("Bad type params");
}
