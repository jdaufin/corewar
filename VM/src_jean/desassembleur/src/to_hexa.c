/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonthie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 18:18:11 by jgonthie          #+#    #+#             */
/*   Updated: 2017/12/30 16:01:03 by jgonthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crack.h"

char	*to_hexa(unsigned char c1, unsigned char c2)
{
	char	*join;
	char	*o1;
	char	*o2;

	o1 = ft_strbase(c1, "0123456789abcdef");
	if (ft_strlen(o1) == 1 && o1[0] == '0')
	{
		ft_strdel(&o1);
		o1 = ft_strdup("00");
	}
	o2 = ft_strbase(c2, "0123456789abcdef");
	if (ft_strlen(o2) == 1 && o2[0] == '0')
	{
		ft_strdel(&o2);
		o2 = ft_strdup("00");
	}
	join = ft_strjoin(o1, o2);
	ft_strdel(&o1);
	ft_strdel(&o2);
	return (join);
}
