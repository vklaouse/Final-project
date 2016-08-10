/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 11:29:19 by semartin          #+#    #+#             */
/*   Updated: 2016/06/06 11:29:20 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_init_proc : Initialise one new proc for each champ in parameter
**	---------------------------------------------------------------------------
**	init_g_prog : Initisalise g->prog variable and create the t_list
**	---------------------------------------------------------------------------
**	ft_cycle_to_die : Every Cycle to die check :
**						--> The process that need to die
**								If 0 proc are alive : exit
**						--> The number of lives done since the last CTD
**								If lives > NBR_LIVE	: Decrease CDT by delta
**						--> If check is > 10
**								if check > 10 : Decrease CDT by delta
**						--> Otherwise increase check by one
**	---------------------------------------------------------------------------
**	core_vm : Core of the VM :
**				--> Call init prog
**				--> Kill champ
**				--> Launch the visualisator if -v is called
**	---------------------------------------------------------------------------
**	ft_corewar : MAIN Loop :
**					--> Inscrease cycle by one every loop
**					--> Call ft_algo and core_vm
**					--> If -v loop the mlx (graphic library)
*/

static t_proc	*ft_init_proc(t_glob *g, int i)
{
	int		j;
	t_proc	*p;

	if (!(p = malloc(sizeof(*p))))
		ft_error("Allocation Error : Insufficient memory");
	p->player = -1 - i;
	p->number = i + 1;
	p->pc = ((double)i / (double)g->nb_champ) * MEM_SIZE;
	p->carry = 1;
	p->live = 0;
	p->last_live = 0;
	p->wait = -1;
	p->old_pc = -1;
	if (!(p->instr = malloc(sizeof(t_byte) * 16))
		|| !(p->r = malloc(sizeof(int) * 16))
		|| !(p->code = malloc(sizeof(int) * 4)))
		ft_error("Allocation Error : Insufficient memory");
	j = -1;
	while (++j < 16)
	{
		p->instr[j] = 0;
		p->r[j] = 0;
	}
	p->r[0] = p->player;
	return (p);
}

static void		init_g_prog(t_glob *g)
{
	int		i;
	t_list	*lst;
	t_list	*tmp;
	t_proc	*p;

	lst = NULL;
	g->prog->nb_proc = g->nb_champ;
	g->prog->cycle_to_die = CYCLE_TO_DIE;
	g->prog->cycle = 1;
	g->prog->check = 0;
	g->prog->all_cycle = 1;
	g->prog->live = 0;
	g->prog->nb_proc = g->nb_champ;
	if (g->param->v)
		visualisateur(g);
	i = 0;
	while (i < g->nb_champ)
	{
		p = ft_init_proc(g, i);
		tmp = ft_lstnew(p, sizeof(p));
		ft_lstadd(&lst, tmp);
		i++;
	}
	g->begin_lst = lst;
}

static void		ft_cycle_to_die(t_glob *g)
{
	if (g->prog->live >= NBR_LIVE)
	{
		g->prog->cycle_to_die -= CYCLE_DELTA;
		if (g->param->s_cycles)
			ft_print_cycle_to_die(g);
		if (g->prog->cycle_to_die < 0)
			g->prog->cycle_to_die = 1;
		g->prog->check = 0;
	}
	else if (g->prog->check == MAX_CHECKS - 1)
	{
		g->prog->cycle_to_die -= CYCLE_DELTA;
		g->prog->check = 0;
		if (g->param->s_cycles)
			ft_print_cycle_to_die(g);
		if (g->prog->cycle_to_die < 0)
			g->prog->cycle_to_die = 1;
		g->prog->check = 0;
	}
	else
		g->prog->check += 1;
	g->prog->cycle = 0;
	g->prog->live = 0;
}

static int		core_vm(t_glob *g)
{
	if (g->param->v)
	{
		if (g->prog->all_cycle > 5)
			ft_process(g);
		if (g->prog->all_cycle % 5 == 0)
			modif_legend(g);
	}
	if (g->prog->cycle == g->prog->cycle_to_die)
	{
		ft_kill_champ(g);
		if (g->prog->nb_proc == 0)
			return (0);
		ft_cycle_to_die(g);
	}
	return (1);
}

void			ft_corewar(t_glob *g)
{
	init_g_prog(g);
	while (g->prog->nb_proc > 0)
	{
		if (g->param->s_cycles)
			ft_print_cycle(g);
		ft_algo(g);
		if (g->param->nbr_cycles == g->prog->all_cycle)
		{
			ft_dump(g);
			ft_print_winner(g);
		}
		if (!core_vm(g))
			break ;
		g->prog->cycle += 1;
		g->prog->all_cycle += 1;
	}
	ft_buffer_screen(NULL, 1);
	ft_print_winner(g);
	if (g->param->v)
	{
		modif_legend(g);
		mlx_key_hook(g->e->win, key_hook, g->e);
		mlx_loop(g->e->mlx);
	}
}
