/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deref_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:01:22 by jdaufin           #+#    #+#             */
/*   Updated: 2017/12/01 18:05:52 by jgonthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Search label returns -1 if label doesn't fit, or the instruction's pos
**	otherwise.
**	NB : label_match must be called with the label definition first "xxxx:"
**	and the label as a parameter ":xxxx" then.
*/

static _Bool	label_match(char *def, char *param)
{
	char	*tmp1;
	char	*tmp2;

	if (!(def && param))
		return (0);
	if (!(tmp1 = ft_strchr(def, LABEL_CHAR)))
		return (0);
	tmp1 = ft_strsub(def, 0, ft_strlen(def) - ft_strlen(tmp1));
	if (!(tmp2 = ft_strrchr(param, LABEL_CHAR)))
		return (0);
	tmp2 = ft_strsub(param, 1, ft_strlen(param) - 1);
	return (ft_strequ(tmp1, tmp2));
}

static int	search_label(t_order *prog, char *label)
{
	int		index;

	if (!(prog && label))
		error("[ERR] : search label bad params");
	index = -1;
	while (++index < prog->nb_label)
	{
		if (label_match(prog->label[index], label))
			return (prog->pos);
	}
	return (-1);
}

int			deref_label(t_order **prog, char *label)
{
	int	ret;
	int	i;

	ret = -1;
	i = 0;
	if (!(prog && *prog && label))
		error("[ERR] dereferencing failure : no label or no program");
	while (prog && prog[i] && prog[i]->op_code)
	{
		if (prog[i]->label \
				&& ((ret = search_label(prog[i], label)) >= 0))
			return (ret);
		i++;
	}
	return (ret);
}
