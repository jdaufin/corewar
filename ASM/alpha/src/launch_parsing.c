/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 18:54:28 by jdaufin           #+#    #+#             */
/*   Updated: 2017/11/29 14:40:06 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	realloc_order(t_order **order, int *size)
{
	*size += 1;
	if ((*order = realloc(*order, sizeof(t_order) * (*size * SIZE_STRUCT))) == NULL)
		error("[ERR] : Ft. Realloc Failed\n");
}

static char	skip_blanks(char **s)
{
	if (!(s && *s && **s))
		return (-1);
	while ((**s) == SPACE || (**s) == TAB)
		(*s)++;
	return (0);
}

_Bool	launch_parsing(char *filepath, t_order **tab, t_header *hdr)
{
	t_file		file;
	int			size;
	int			index;
	if (!tab || *tab)
		error("[ERR] : corrupted slot to record instructions");
	if (!filepath || ((file.fd = open(filepath, O_RDONLY /*| O_SYMLINK*/)) < 0))
		error("[ERR] : opening failed on filepath");
	size = 1;
	file.nb_line = 0;
//	tab = ft_memalloc(sizeof(t_order*) * SIZE_STRUCT * size);
	*tab = (t_order *)ft_memalloc(sizeof(t_order) * (SIZE_STRUCT * size));
	while ((file.ret = get_next_line(file.fd, &file.line)) == 1)
	{
		if ((skip_blanks(&file.line) == -1) || ((*file.line == COMMENT_CHAR)\
					|| !(*file.line)))
			continue ;
		if (*file.line == DOT)
		{
			if (!pars_info(hdr, file.line))
				return (0);
			ft_printf(".name = %s, .comment = %s\n", hdr->prog_name, hdr->comment);
		}
		else
		{
			if (file.nb_line == (SIZE_STRUCT * size))
				realloc_order(tab, &size);
			tab[file.nb_line] = ft_memalloc(sizeof(t_order));
			if (!pars_order(tab[file.nb_line], file))//exit if returns 0?
				return (0);
			index = -1;
			while (++index < tab[file.nb_line]->nb_param)
			ft_printf("param[i]: %s, ty_param[i]: %d\n", tab[file.nb_line]->param[index], tab[file.nb_line]->ty_param[index]);
			file.nb_line += tab[file.nb_line]->op_code ? 1 : 0;
		}
		hdr->nb_struct = file.nb_line;
	}
	return (1);
}