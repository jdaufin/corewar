/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonthie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:00:06 by jgonthie          #+#    #+#             */
/*   Updated: 2018/01/05 16:48:43 by jgonthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	print_corewar(t_info *info)
{
	mvwprintw(info->win, (HEIGHT_WIN / 2) - 12, 75, " ________  ________\
________  _______   ___       __   ________  ________     ");
	mvwprintw(info->win, (HEIGHT_WIN / 2) - 11, 75, "|\\   ____\\|\\   __\
\\|\\   __  \\|\\  ___ \\ |\\  \\     |\\  \\|\\   __  \\|\\   __  \\    ");
	mvwprintw(info->win, (HEIGHT_WIN / 2) - 10, 75, "\\ \\  \\___|\\ \\  \\|\\\
\\ \\  \\|\\  \\ \\   __/|\\ \\  \\    \\ \\  \\ \\  \\|\\  \\ \\  \\|\\  \\   ");
	mvwprintw(info->win, (HEIGHT_WIN / 2) - 9, 75, " \\ \\  \\    \\ \\  \\\\\\ \
\\ \\   _  _\\ \\  \\_|/_\\ \\  \\  __\\ \\  \\ \\   __  \\ \\   _  _\\  ");
	mvwprintw(info->win, (HEIGHT_WIN / 2) - 8, 75, "  \\ \\  \\____\\ \\  \
\\\\\\  \\ \\  \\\\  \\\\ \\  \\_|\\ \\ \\  \\|\\__\\_\\ \
\\ \\  \\ \\  \\ \\  \\\\  \\| ");
	mvwprintw(info->win, (HEIGHT_WIN / 2) - 7, 75, "   \\ \\_______\\ \
\\_______\\ \\__\\\\ _\\\\ \\_______\\ \\____________\\ \\__\\ \\__\\ \\
\__\\\\ _\\ ");
	mvwprintw(info->win, (HEIGHT_WIN / 2) - 6, 75, "    \\|______\
_|\\|_______|\\|__|\\|__|\\|_______|\\|____________|\\|__|\\|__|\\|__|\\|__|");
}

static	void	choice_of_music(FMOD_CHANNELGROUP *canal, FMOD_SYSTEM *system,
		FMOD_SOUND *bgm[4], int i)
{
	FMOD_BOOL state;

	FMOD_ChannelGroup_GetPaused(canal, &state);
	if (state == false )
	{
		FMOD_ChannelGroup_Stop(canal);
		FMOD_Sound_SetLoopCount(bgm[i], -1);
		FMOD_System_PlaySound(system, bgm[i], 0, false, NULL);
	}
	else
	{
		FMOD_Sound_SetLoopCount(bgm[i], -1);
		FMOD_System_PlaySound(system, bgm[i], 0, false, NULL);
	}
}

static void		manage_music(t_info *info)
{
	FMOD_CHANNELGROUP *c;
	char p;

	FMOD_System_GetMasterChannelGroup(info->s, &c);
	while (1)
	{
		p = wgetch(info->win);
		if (p == 'p')
			FMOD_ChannelGroup_Stop(c);
		else if (p == ' ')
		{
			FMOD_System_PlaySound(info->s, info->bgm[3], 0, false, NULL);
			break ;
		}
		else if (p == '1')
			choice_of_music(c, info->s, info->bgm, 0);
		else if (p == '2')
			choice_of_music(c, info->s, info->bgm, 1);
		else if (p == '3')
			choice_of_music(c, info->s, info->bgm, 2);
	}
}

static	void	draw_menu(t_info *info)
{
	wattron(info->win, COLOR_PAIR(3));
	print_corewar(info);
	wattron(info->win, A_UNDERLINE);
	mvwprintw(info->win, (HEIGHT_WIN / 2) + 3, 106, "PRESS SPACE TO BEGIN");
	wattroff(info->win, A_UNDERLINE);
	mvwprintw(info->win, 70, 10, "By : JDaufin");
	mvwprintw(info->win, 68, 200, "Choose a bgm song with 1, 2, 3");
	mvwprintw(info->win, 72, 10, "     JPallard");
	mvwprintw(info->win, 70, 200, "1 = choosen by jdaufin ");
	mvwprintw(info->win, 74, 10, "     JGonthie");
	mvwprintw(info->win, 72, 200, "2 = choosen by jpallard");
	mvwprintw(info->win, 74, 200, "3 = choosen by jgonthie");
	wrefresh(info->win);
	manage_music(info);
	wattroff(info->win, COLOR_PAIR(3));
}

void		put_menu(t_info *info)
{
	new_win(info, MENU);
	draw_menu(info);
	destroy_win(info);
}
