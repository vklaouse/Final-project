/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instr_live.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 16:15:41 by semartin          #+#    #+#             */
/*   Updated: 2016/05/11 16:15:42 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	is_champ : Return 1 if the int is one of the player
** 	---------------------------------------------------------------------------
**	live_show_op : Update champion life + Show op if -op
**	---------------------------------------------------------------------------
**	show_live : If -live : Show when ever live is called by a champion
**	---------------------------------------------------------------------------
** 	proc_live : If the instr buffer is at 5, read the number player
**				and increase nb_live and then clear the buffer
**				Can give a live to an other champ aswell
**				Oterwise add one byte into the buffer and return
**				Wait 10 cycle to execute
*/

static int	is_champ(t_glob *g, int player)
{
	int i;

	i = 0;
	while (i < g->nb_champ)
	{
		if (-1 - i == player)
			return (1);
		else
			i++;
	}
	return (0);
}

static void	live_show_op(t_glob *g, t_proc *p, int player)
{
	char	*s;
	char	*tmp;
	int		i;
	int		nb;

	if (g->param->s_op)
	{
		if (!(s = malloc(sizeof(*s) * 64)))
			ft_error("Allocation Error : Insufficient memory");
		tmp = s;
		i = 0;
		nb = number_digit(p->number);
		ft_strcpy(tmp++, "P");
		while (i++ < 5 - nb)
			ft_strcpy(tmp++, " ");
		ft_itoa_cpy(p->number, (tmp = tmp + ft_strlen(tmp)));
		ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | live ");
		ft_itoa_cpy(player, (tmp = tmp + ft_strlen(tmp)));
		ft_strcpy((tmp = tmp + ft_strlen(tmp)), "\n");
		ft_buffer_screen(s, 0);
		free(s);
	}
	if (g->param->s_pc)
		ft_print_pc(g, p, 5);
}

static void	show_live(int player, t_glob *g)
{
	char *s;
	char *tmp;

	g->champ[-1 - player]->nb_live += 1;
	g->champ[-1 - player]->last_live = g->prog->all_cycle;
	if (g->param->s_lives)
	{
		if (!(s = malloc(sizeof(*s) * 64)))
			ft_error("Allocation Error : Insufficient memory");
		tmp = s;
		ft_strcpy(tmp, "Player ");
		ft_itoa_cpy(-player, (tmp = tmp + 7));
		ft_strcpy((tmp = tmp + ft_strlen(tmp)), " (");
		ft_strcpy((tmp = tmp + 2), g->champ[-1 - player]->name);
		ft_strcpy((tmp = tmp + ft_strlen(tmp)), ") is said to be alive\n");
		ft_buffer_screen(s, 0);
		free(s);
	}
}

void		ft_proc_live(t_proc *p, t_glob *g)
{
	int player;
	int i;

	if (p->wait == -1)
		p->wait = 7;
	else if (p->wait > 0)
		p->wait -= 1;
	else
	{
		i = 0;
		while (++i < 5)
			p->instr[i] = g->arena[(p->pc + i) % MEM_SIZE];
		player = byte_into_int(&(p->instr[1]));
		p->live += 1;
		p->last_live = g->prog->all_cycle;
		g->prog->live += 1;
		live_show_op(g, p, player);
		if (is_champ(g, player))
			show_live(player, g);
		clear_byte(p->instr);
		p->wait = -1;
		p->pc += 5;
	}
}
