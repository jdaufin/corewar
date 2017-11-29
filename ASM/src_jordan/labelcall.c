/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labelcall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpallard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 11:44:04 by jpallard          #+#    #+#             */
/*   Updated: 2017/11/27 17:40:14 by jpallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/jordan.h"
#include "../../include/op.h"

void	timetoatoi(unsigned int j, unsigned char c, char *param, int fd)
{
	unsigned short s;

	if (c > 0)
	{
		c = ft_atoi(param);
		write(fd, &c, 1);
	}
	else if (j > 0)
	{
		j = ft_atoi(param);
		bigendian(&j, 0);
		write(fd, &j, 4);
	}
	else
	{
		s = ft_atoi(param);
		bigendian(0, &s);
		write(fd, &s, 2);
	}
}

void	labelcall(t_order **champ, int fd, char *label, int fpos)
{
	unsigned short	pos;
	short			res;
	unsigned short	max;

	pos = deref_label(champ, label);
	res = pos - fpos;
	max = 0xFFFF;
	if (res < 0)
	{
		max = max + res + 1;
		bigendian(0, &max);
		write(fd, &max, 2);
	}
	else
	{
		pos = res;
		bigendian(0, &pos);
		write(fd, &pos, 2);
	}
}