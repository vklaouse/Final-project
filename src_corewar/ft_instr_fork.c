/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instr_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 20:02:12 by semartin          #+#    #+#             */
/*   Updated: 2016/05/19 20:02:12 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/libft.h"

/*
**	ft_flag_2 : 2nd part for flag fork (norme)
**	---------------------------------------------------------------------------
**	ft_flag_fork :	If option -op : Add the operation to the buffer
**					that will be printed on screen
**	---------------------------------------------------------------------------
**	ft_init_variable : Usefull fcnt that init p->proc : new (norme)
**	---------------------------------------------------------------------------
**	ft_init_new_proc : Create a new proc, allocate it dynamic memory
**						Cpy everything from his father process
**						Exept the PC (prog counter)
** ----------------------------------------------------------------------------
**	ft_proc_fork : Creat a new process : fork acess at max IDX_MOD memory
**					While lfork can acess anywhere.
**					However lfork is slower to execute than fork.
**					lfork need 1000 cycles and fork 800 cycles
*/

static void	ft_flag_2(t_proc *p, int mod, char *tmp)
{
	ft_itoa_cpy(byte_into_short(&(p->instr[1])), (tmp += ft_strlen(tmp)));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), " (");
	if (p->pc + (byte_into_short(&(p->instr[1])) % mod) > 0)
		ft_itoa_cpy((p->pc + (byte_into_short(&(p->instr[1])) % mod))
				% MEM_SIZE, (tmp += 2));
	else
		ft_itoa_cpy((MEM_SIZE + (p->pc + (byte_into_short(&(p->instr[1]))
				% mod))) % MEM_SIZE, (tmp += 2));
	ft_strcpy((tmp = tmp + ft_strlen(tmp)), ")\n");
}

static void	ft_flag_fork(t_glob *g, t_proc *p, int mod)
{
	int		i;
	int		nb;
	char	*s;
	char	*tmp;

	if (g->param->s_op)
	{
		s = malloc(sizeof(*s) * 64);
		tmp = s;
		i = 0;
		nb = number_digit(p->number);
		ft_strcpy(tmp++, "P");
		while (i++ < 5 - nb)
			ft_strcpy(tmp++, " ");
		ft_itoa_cpy(p->number, tmp);
		if (mod == MEM_SIZE)
			ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | lfork ");
		else
			ft_strcpy((tmp = tmp + ft_strlen(tmp)), " | fork ");
		ft_flag_2(p, mod, tmp);
		ft_buffer_screen(s, 0);
		free(s);
	}
}

static void	ft_init_variable(t_proc *new, t_proc *p, int number)
{
	new->carry = p->carry;
	new->live = 0;
	new->last_live = p->last_live;
	new->wait = -1;
	new->wait = -1;
	new->old_pc = -1;
	new->number = number;
}

static void	ft_init_new_proc(t_glob *g, t_proc *p, int mod, int number)
{
	t_proc	*new;
	t_list	*tmp;
	int		i;

	if (!(new = malloc(sizeof(*new))))
		ft_error("Allocation Error : Insufficient memory");
	new->player = p->player;
	if (p->pc + (byte_into_short(&(p->instr[1])) % mod) > 0)
		new->pc = (p->pc + (byte_into_short(&(p->instr[1])) % mod)) % MEM_SIZE;
	else
		new->pc = (MEM_SIZE + (p->pc + (byte_into_short(&p->instr[1]) % mod)));
	ft_flag_fork(g, p, mod);
	ft_init_variable(new, p, number);
	if (!(new->r = malloc(sizeof(int) * 16)))
		ft_error("Allocation Error : Insufficient memory");
	reg_cpy(p->r, new->r);
	if (!(new->instr = malloc(sizeof(t_byte) * 16)))
		ft_error("Allocation Error : Insufficient memory");
	if (!(new->code = malloc(sizeof(int) * 4)))
		ft_error("Allocation Error : Insufficient memory");
	i = 0;
	while (i < 16)
		new->instr[i++] = 0;
	tmp = ft_lstnew(new, sizeof(new));
	ft_lstadd(&(g->begin_lst), tmp);
}

void		ft_proc_fork(t_proc *p, t_glob *g, int n)
{
	int			mod;
	static int	number = 0;
	int			i;

	if (number == 0)
		number = g->nb_champ + 1;
	if (p->wait == -1)
		p->wait = (n == 0) ? 797 : 997;
	else if (p->wait > 0)
		p->wait -= 1;
	else
	{
		mod = (n == 0) ? IDX_MOD : MEM_SIZE;
		i = 0;
		while (++i < 3)
			p->instr[i] = g->arena[(p->pc + i) % MEM_SIZE];
		ft_init_new_proc(g, p, mod, number++);
		g->prog->nb_proc += 1;
		p->wait = -1;
		if (g->param->s_pc)
			ft_print_pc(g, p, 3);
		p->pc += 3;
		clear_byte(p->instr);
	}
}
