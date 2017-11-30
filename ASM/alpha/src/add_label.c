/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 22:31:58 by jdaufin           #+#    #+#             */
/*   Updated: 2017/11/30 19:54:13 by jgonthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_label(t_order **slot, char *s)
{
	char	**buf;
	_Bool	resize;
	ssize_t	i;

	if (!(slot && *slot && s))
		return ;
	resize = (*slot)->label ? 1 : 0;
	if (!(*slot)->label)
		(*slot)->label = (char **)ft_memalloc(sizeof(char *) * 2);
	buf = (*slot)->label;
	i = -1;
	while (buf[++i])
		;
	if (resize)
	{
		if (((*slot)->label = (char **)realloc((void **)&((*slot)->label),
						(i + 2) * sizeof(char *))) == NULL)
			error("[ERR] : ft.Realloc() Failed");
		buf = (*slot)->label;
	}
	buf[i] = ft_strdup(s);
	(*slot)->nb_label++;
}
