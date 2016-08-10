/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 13:36:16 by jschotte          #+#    #+#             */
/*   Updated: 2016/06/13 15:16:58 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"

char	*change_ext(char *str)
{
	char	*dot;
	char	*new;
	int		lengt;

	dot = ft_strrchr(str, '.');
	lengt = dot - str;
	new = malloc(sizeof(new) * (lengt + 5));
	ft_strncpy(new, str, lengt);
	ft_strcpy(new + lengt, ".cor");
	return (new);
}

char	check_type_param(t_par *param, int x2, int x1)
{
	char val;

	val = 0;
	if (param->size == 4)
		return (ft_puissance(2, x1) + ft_puissance(2, x2));
	else if (ft_strcmp(ft_strsub(param->p, 0, 1), "r") == 0
			&& ft_strlen(param->p) > 1)
		return (ft_puissance(2, x2));
	else if (ft_strcmp(ft_strsub(param->p, 0, 1), "%") == 0
			|| ft_strcmp(ft_strsub(param->p, 0, 1), ":") == 0)
	{
		if (ft_strcmp(ft_strsub(param->p, 0, 1), "%") == 0)
			return (ft_puissance(2, x1));
		else
			return (ft_puissance(2, x1) + ft_puissance(2, x2));
	}
	else
		return (0);
}

int		check_type_param_int(t_par *param, int x2, int x1)
{
	int val;

	val = 0;
	if (param->size == 4)
		return (ft_power(2, x1) + ft_power(2, x2));
	else if (ft_strcmp(ft_strsub(param->p, 0, 1), "r") == 0
			&& ft_strlen(param->p) > 1)
		return (ft_power(2, x2));
	else if (ft_strcmp(ft_strsub(param->p, 0, 1), "%") == 0
			|| ft_strcmp(ft_strsub(param->p, 0, 1), ":") == 0)
	{
		if (ft_strcmp(ft_strsub(param->p, 0, 1), "%") == 0)
			return (ft_power(2, x1));
		else
			return (ft_power(2, x1) + ft_power(2, x2));
	}
	else
		return (0);
}

void	check_all_par(t_inst *inst)
{
	t_inst *tmp_inst;

	tmp_inst = inst;
	while (tmp_inst != '\0')
	{
		if (tmp_inst->opcode != 1 && tmp_inst->opcode != 9
			&& tmp_inst->opcode != 12 && tmp_inst->opcode != 15)
			check_octetcode(tmp_inst->opcode,
				get_octet_code_int(tmp_inst->par));
		else if (tmp_inst->opcode == 1 && tmp_inst->par->size == 4)
			ft_exit("Bad type params");
		tmp_inst = tmp_inst->next;
	}
}

void	encode(char *str, t_label *label, t_inst *inst, t_n_c *n_c)
{
	int		fd;
	int		pfd;

	check_all_par(inst);
	pfd = open(change_ext(str), O_WRONLY | O_CREAT
			| O_TRUNC | O_SYNC, S_IRUSR | S_IWUSR);
	if (pfd != -1)
	{
		fd = open(str, O_RDONLY);
		if (fd != -1)
		{
			print_header(inst, n_c, pfd);
			print_inst(label, inst, pfd);
			ft_putstr("Writing output to ");
			ft_putendl(change_ext(str));
			close(fd);
		}
		else
			ft_exit("File not found");
		close(pfd);
	}
	else
		ft_exit("Fail to create file");
}
