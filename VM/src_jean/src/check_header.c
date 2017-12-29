/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpallard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:00:13 by jpallard          #+#    #+#             */
/*   Updated: 2017/12/29 18:17:58 by jgonthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		littleendian(unsigned int *i)
{
	if (i != 0)
	{
		*i = ((*i >> 24) & 0xff)
			| ((*i << 8) & 0xff0000)
			| ((*i >> 8) & 0xff00)
			| ((*i << 24) & 0xff000000);
	}
}

static char	*get_name(int fd)
{
	char	name[PROG_NAME_LENGTH + 1];

	ft_bzero(name, PROG_NAME_LENGTH + 1);
	lseek(fd, 4, SEEK_SET);
	read(fd, name, PROG_NAME_LENGTH);
	return (ft_strdup(name));
}

static void		init_proc(t_proc ***p, int fd)
{
	static int	color = 1;

	(**p) = ft_memalloc(sizeof(t_proc));
	(**p)->color = color;
	(**p)->carry = 0;
	(**p)->pc = 0;
	(**p)->cc = 0;
	(**p)->champ.id = 0;
	(**p)->children = NULL;
	(**p)->champ.name = get_name(fd);
	color++;
}

/*
 **check if each champ have the correct header attached to them and if the size 
 **is correct
 */

void	parse_header(int fd, t_proc **p, char *name_file)
{
	unsigned int	i[1];
	unsigned int	j;

	read(fd, i, 4);
	littleendian(&i[0]);
	if (*i != COREWAR_EXEC_MAGIC)
	{
		ft_printf("Error : %s has an invalid header", name_file);
		error_vm("");
	}
	init_proc(&p, fd);
	lseek(fd, PROG_NAME_LENGTH + 8, SEEK_SET);
	read(fd, i, 4);
	littleendian(&i[0]);
	if (*i > CHAMP_MAX_SIZE)
		error_vm("Error : Champ too big");
	else if (*i <= 0)
		error_vm("Error : Champ size is 0 or negative ?");
	j = lseek(fd, 0, SEEK_END);
	if (*i + PROG_NAME_LENGTH + COMMENT_LENGTH + (sizeof(int) * 4) != j)
		error_vm("Error : Diff between file size and header prog_size");
}
