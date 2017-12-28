/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpallard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 16:32:14 by jpallard          #+#    #+#             */
/*   Updated: 2017/12/28 16:34:26 by jpallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jordan.h"

void	carry(t_proc ***p, unsigned int val)
{
	if (val != 0)
		(**p)->carry = 0;
	else
		(**p)->carry = 1;
}