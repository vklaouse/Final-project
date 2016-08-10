/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 14:47:07 by semartin          #+#    #+#             */
/*   Updated: 2016/06/06 20:11:57 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	check_number : Check if the argt is a number or not, if it's not exit
**	---------------------------------------------------------------------------
**	init : Initilise g variable (and alloc g->name_files)
**	---------------------------------------------------------------------------
**	flag : Check if flag are valid and fill name_files
**	---------------------------------------------------------------------------
**	parse_flags : Parse argv to split flags and champion names
*/

static int	ft_check_number(char **av, t_glob *g, int ac)
{
	int	tmp;

	g->cnt++;
	tmp = 0;
	if (g->cnt >= ac)
		ft_error("Error");
	tmp = ft_atoi(av[g->cnt]);
	if ((ft_strcmp(av[g->cnt], ft_itoa(tmp))))
		ft_error("Error");
	if (tmp < 1)
		ft_error("Error");
	return (tmp);
}

static void	ft_init(t_glob *g)
{
	int i;

	if (!(g->name_files = malloc(sizeof(char *) * (5))))
		ft_error("Allocation Error : Insufficient memory");
	if (!(g->number_champ = malloc(sizeof(int) * (4))))
		ft_error("Allocation Error : Insufficient memory");
	i = 0;
	while (i < 4)
		g->number_champ[i++] = 0;
	g->cnt = 0;
	g->param->v = 0;
	g->param->a = 0;
	g->param->nbr_cycles = 0;
	g->nb_champ = 0;
	g->param->s_lives = 0;
	g->param->s_cycles = 0;
	g->param->s_op = 0;
	g->param->s_deaths = 0;
	g->param->s_pc = 0;
}

static void	ft_flag(t_glob *g, char **av, int *i)
{
	if (!ft_strcmp("-death", av[g->cnt]) && g->param->s_deaths == 0)
		g->param->s_deaths = 1;
	else if (!ft_strcmp("-cycle", av[g->cnt]) && g->param->s_cycles == 0)
		g->param->s_cycles = 1;
	else if (!ft_strcmp("-op", av[g->cnt]) && g->param->s_op == 0)
		g->param->s_op = 1;
	else if (!ft_strcmp("-live", av[g->cnt]) && g->param->s_lives == 0)
		g->param->s_lives = 1;
	else if (!ft_strcmp("-pc", av[g->cnt]) && g->param->s_pc == 0)
		g->param->s_pc = 1;
	else if (av[g->cnt][ft_strlen(av[g->cnt]) - 1] != 'r'
		|| av[g->cnt][ft_strlen(av[g->cnt]) - 2] != 'o'
		|| av[g->cnt][ft_strlen(av[g->cnt]) - 3] != 'c'
		|| av[g->cnt][ft_strlen(av[g->cnt]) - 4] != '.')
		ft_error("Error : Wrong usage");
	else
	{
		g->name_files[(*i)++] = av[g->cnt];
		g->name_files[*i] = NULL;
	}
}

static void	verbose(void)
{
	ft_putstr("Usage: ./corewar [-a -v -n N -dump N -live -cycle -op -death");
	ft_putstr(" -pc] <champion1.cor> <...>\n");
	ft_putstr("   -a      : Aff ;D\n");
	ft_putstr("-------- TEXT OUTPUT MODE ---------\n");
	ft_putstr("   -n    N : Change the name of the next champion\n");
	ft_putstr("   -dump N : Runs N cycles\n");
	ft_putstr("   -live   : Show lives\n");
	ft_putstr("   -cycle  : Show cycles\n");
	ft_putstr("   -op     : Show operations\n");
	ft_putstr("   -death  : Show deaths\n");
	ft_putstr("   -pc     : Show PC movements (Except for jumps)\n");
	ft_putstr("-------- VISUALISATEUR MODE -------\n");
	ft_putstr("   -v      : Minilibx visualisateur\n");
	ft_putstr("-----------------------------------\n");
	exit(0);
}

void		parse_flags(t_glob *g, char **av, int ac)
{
	int	i;

	i = 0;
	ft_init(g);
	while (g->cnt < ac)
	{
		if (!ft_strcmp("-v", av[g->cnt]) && g->param->v == 0)
			g->param->v = 1;
		else if (!ft_strcmp("-a", av[g->cnt]) && g->param->a == 0)
			g->param->a = 1;
		else if (!ft_strcmp("-n", av[g->cnt]) && g->number_champ[i] == 0)
		{
			if (i > 3)
				ft_error("Error : Wrong usage");
			g->number_champ[i] = ft_check_number(av, g, ac);
		}
		else if (!ft_strcmp("-dump", av[g->cnt]) && g->param->nbr_cycles == 0)
			g->param->nbr_cycles = ft_check_number(av, g, ac);
		else
			ft_flag(g, av, &i);
		g->cnt++;
	}
	g->nb_champ = i;
	if (!g->nb_champ)
		verbose();
}
