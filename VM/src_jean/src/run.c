/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpallard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 12:13:34 by jpallard          #+#    #+#             */
/*   Updated: 2017/12/28 11:40:25 by jgonthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	execute_order() checks that the process has been called on enough cycles
**	and then calls the operation execution function associated with the opcode
*/

void	execute_order(unsigned char *mem, t_proc *p)
{
	int		i;

	i = 0;
	while (i < 17)
	{
		if (mem[p->pc] == g_op_tab[i].op_code)
		{
			if (++(p->cc) == (unsigned int)g_op_tab[i].cycles)
			{
				g_op_tab[i].func(&p, mem);
				p->cc = 0;
			}
			return ;
		}
		i++;
	}
	p->pc++;
	p->pc %= MEM_SIZE;
}

/*
**	The run function manages the cycles, it stops only when there is no
**	more processus alive.
*/

void	run(unsigned char *mem, t_proc **p)
{
	_Bool	c;
	ssize_t	i;

	if (!(mem && p))
		return ;
	c = 1;
	while (c)
	{
		while (timer(CHECK) < deadline(CHECK))
		{
			i = (ssize_t)g_n_players;
			while (--i >= 0)
				execute_order(mem, p[i]);
			timer(INCR);
		}
		timer(REINIT);
		c = 0;
		atropos(p, g_n_players);
		while (++i < (ssize_t)g_n_players)
			c |= p[i] ? 1 : 0;
		deadline(DECR);
	}
}
