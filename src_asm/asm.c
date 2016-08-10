/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 09:26:00 by jschotte          #+#    #+#             */
/*   Updated: 2016/06/10 16:08:25 by aputzolu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"

int		valid_file(t_srcs *srcs)
{
	t_error *tmp;

	if ((tmp = srcs->error) == NULL)
		return (1);
	while (tmp)
	{
		if (tmp->str != NULL)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	do_flags(char **argv, t_srcs **srcs)
{
	int i;

	i = 2;
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "-p"))
			print((*srcs)->inst, (*srcs)->label, (*srcs)->n_c);
		i++;
	}
	free_all(srcs);
}

int		bad_file(char **argv)
{
	char *sub;

	if ((sub = ft_strsub(argv[1], ft_strlen(argv[1]) - 2, 2)) == NULL)
		return (1);
	if (!ft_strcmp(sub, ".s"))
		return (0);
	return (1);
}

void	print_usage(void)
{
	ft_putstr_fd("Usage: ./asm <sourcefile.s> [-p] \n  "
	" -p :Print parsing\n", 2);
}

int		main(int argc, char **argv)
{
	t_label	*label;
	t_inst	*inst;
	t_n_c	*n_c;
	t_error	*error;
	t_srcs	*srcs;

	label = NULL;
	inst = NULL;
	n_c = create_name();
	error = NULL;
	srcs = create_srcs(inst, label, n_c, error);
	if (argc > 1)
	{
		if (bad_file(argv))
			ft_exit(ft_strjoin("Can't read source file ", argv[1]));
		if (parsing(argv[1], &srcs) == 0)
			ft_exit("File Error");
		if (valid_file(srcs))
			encode(argv[1], srcs->label, srcs->inst, srcs->n_c);
		else
			ft_print_error(srcs);
		do_flags(argv, &srcs);
	}
	else
		print_usage();
}
