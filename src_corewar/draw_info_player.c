/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:42:31 by jdaufin           #+#    #+#             */
/*   Updated: 2018/02/08 15:53:26 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	p_tracer(t_info *info, int y, int *(*val)[2], t_proc *tmp)
{
	mvwprintw(info->win, y + 7, BORDER_ARENA_X + 5, "Last live : ");
	wprintw(info->win, store_nb(INCR, ft_itoa(player_lives(CHECK,\
						val, info, tmp))));
	mvwprintw(info->win, y + 8, BORDER_ARENA_X + 5, "Lives in current \
period : ");
	wprintw(info->win, store_nb(INCR, ft_itoa(player_lives(NONE, \
								val, info, tmp))));
}

static void	w_tracer(t_info *info, int y, int color, t_proc *tmp)
{
	wattron(info->win, A_STANDOUT);
	wattron(info->win, COLOR_PAIR(tmp->color));
	mvwprintw(info->win, y, BORDER_ARENA_X + 14, "   ");
	mvwprintw(info->win, y, BORDER_ARENA_X + 19, "    ");
	mvwprintw(info->win, y + 1, BORDER_ARENA_X + 13, "   ");
	mvwprintw(info->win, y + 1, BORDER_ARENA_X + 18, "      ");
	mvwprintw(info->win, y + 2, BORDER_ARENA_X + 15, " ");
	mvwprintw(info->win, y + 2, BORDER_ARENA_X + 17, "    ");
	mvwprintw(info->win, y + 2, BORDER_ARENA_X + 22, "  ");
	mvwprintw(info->win, y + 3, BORDER_ARENA_X + 17, "   ");
	mvwprintw(info->win, y + 3, BORDER_ARENA_X + 21, " ");
	mvwprintw(info->win, y + 4, BORDER_ARENA_X + 18, "  ");
	wattroff(info->win, COLOR_PAIR(color));
	wattroff(info->win, A_STANDOUT);
}

void		draw_info_player(t_info *info, t_proc **proc, int color)
{
	t_proc	*tmp;
	int		y;
	int		*val[2];

	y = 18;
	tmp = (*proc);
	val[0] = NULL;
	while (tmp)
	{
		if (id_is_new(CHECK, tmp->champ.id))
		{
			val[1] = &(tmp->champ.id);
			w_tracer(info, y, color, tmp);
			p_tracer(info, y, &val, tmp);
			color++;
			y += 12;
		}
		tmp = tmp->next;
	}
	store_nb(REINIT, NULL);
	id_is_new(REINIT, INT_MAX);
	wrefresh(info->win);
}