/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:30:38 by jdaufin           #+#    #+#             */
/*   Updated: 2018/01/31 15:24:06 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

_Bool	chronos(t_proc *proc, t_req request, unsigned int player)
{
	t_info	*info;

	if (!proc)
		return (0);
	if (request == LIVE)
	{
		info = get_info(NULL);
		proc->life.status = 1;
		proc->life.last = global_timer(CHECK);
		proc->life.player = player;
		nbr_live(INCR);
		if (info)
			lives_reg(LIVE, player, info, proc);
		/*
		else //dbg else
		{
			ft_printf("info @ %p, ", info);
			if (info)
				ft_printf("-c option = %s\n", info->opt[0] ? "TRUE" : "FALSE");
		}
		*/
		return (1);
	}
	else if (request == CHECK)
		return (proc->life.status);
		//return ((proc->life.player == player) && proc->life.status);
	//incomplete : handle the association between player numbers and all
	//processes live declarations
	return (0);
}