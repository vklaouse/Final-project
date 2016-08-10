/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 12:16:18 by semartin          #+#    #+#             */
/*   Updated: 2016/05/20 12:16:19 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	nb_live : Count the nbr of lives called for each champ
**	----------------------------------------------------------------------------
**	kill_proc : Remove the dead process from the list, free what's needed
**	----------------------------------------------------------------------------
**	kill_champ : Find out what champ need to die
**				(If they didn't call a live for the past Cycle_to_die)
*/

int			ft_nb_live(t_glob *g)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (i < g->nb_champ)
	{
		nb += g->champ[i]->nb_live;
		i++;
	}
	return (nb);
}

static void	ft_death(t_glob *g, t_proc *p)
{
	char *s;
	char *tmp;

	s = malloc(sizeof(*s) * 64);
	tmp = s;
	ft_strcpy(tmp, "Process ");
	ft_itoa_cpy(p->number, tmp += 8);
	ft_strcpy((tmp += ft_strlen(tmp)), " hasn't live for ");
	ft_itoa_cpy(g->prog->all_cycle - p->last_live, tmp += 17);
	ft_strcpy((tmp += ft_strlen(tmp)), " cycles (CTD ");
	ft_itoa_cpy(g->prog->cycle_to_die, tmp += 13);
	ft_strcpy((tmp += ft_strlen(tmp)), ")\n");
	ft_buffer_screen(s, 0);
	free(s);
}

static void	ft_kill_proc(t_list **begin_lst, t_list *kill, t_glob *g)
{
	t_proc	*p;
	t_list	*tmp;

	p = kill->content;
	if (kill == *begin_lst)
		*begin_lst = kill->next;
	else
	{
		tmp = *begin_lst;
		while (tmp->next != kill)
			tmp = tmp->next;
		tmp->next = kill->next;
	}
	if (g->param->s_deaths)
		ft_death(g, p);
	free(p->code);
	free(p->r);
	free(p->instr);
	free(p);
	kill->content = NULL;
	kill->content_size = 0;
	kill->next = NULL;
	free(kill);
}

void		ft_kill_champ(t_glob *g)
{
	t_list	**begin_lst;
	t_list	*tmp;
	t_list	*kill;
	t_proc	*p;
	int		i;

	begin_lst = &(g->begin_lst);
	tmp = *begin_lst;
	i = 0;
	while (tmp)
	{
		p = tmp->content;
		if (g->prog->all_cycle - p->last_live >= g->prog->cycle_to_die)
		{
			kill = tmp;
			tmp = tmp->next;
			g->prog->nb_proc -= 1;
			ft_kill_proc(begin_lst, kill, g);
		}
		else
			tmp = tmp->next;
		p = NULL;
	}
}
