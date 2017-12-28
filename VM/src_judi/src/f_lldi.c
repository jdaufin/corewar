/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_lldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:43:20 by jdaufin           #+#    #+#             */
/*   Updated: 2017/12/28 16:20:00 by jdaufin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "judi.h"

static unsigned int lldi_calc(t_proc *proc, unsigned char *mem, int *param,\
		unsigned int (*p_idx)[3])
{
	unsigned int	ret;
	unsigned short	deref[2];
	ssize_t			i;

	i = -1;
	while (++i < 2)
	{
		if (param[i] == T_REG)
			deref[i] = proc->reg[mem[(*p_idx)[i]] - 1];
		//else if (param[i] == T_IND)
		//	deref[i] = chars_to_short(mem, (proc->pc + chars_to_short(mem,\
		//					(*p_idx)[i])));
		else if (param[i] == T_IND)
		{
			unsigned int dbg;

			deref[i] = chars_to_short(mem, ((*p_idx)[i] \
					+ (dbg = chars_to_short(mem, (*p_idx)[i], 1))) % IDX_MOD, 1);
			ft_printf("Intermediate index read on mem[%u] = %u\n", (*p_idx)[i], dbg);
		}
		else
			deref[i] = chars_to_short(mem, (*p_idx)[i], 1);//\
					  // + (param[i] == T_DIR ? 0 : proc->pc);
		ft_printf("deref[%zu(param @ mem[%u])] = %hu\n", i, (*p_idx)[i], deref[i]);//dbg
		ft_printf("proc->pc = %u\n", proc->pc);
	}
	deref[0] = (proc->pc + deref[0] + deref[1]) % MEM_SIZE;
	//deref[0] = (proc->pc + deref[0] + deref[1]) % MEM_SIZE;
	ft_printf("deref sum = %hu\n", deref[0]);//dbg
	return (ret = chars_to_int(mem, deref[0], 1));
}

void	f_lldi(t_proc **proc, unsigned char *mem)
{
	int				*param;
	unsigned int	p_idx[3];
	unsigned int	size;
	unsigned int	val;

	if (!(proc && *proc && mem))
		error_vm("f_lldi() called with undue null parameter(s)");
	param = checkocp(&mem[((*proc)->pc + 1) % MEM_SIZE]);
	size = 2 + param_size(((*proc)->pc + 2) % MEM_SIZE, param, 1, &p_idx);
	if (!parse_params(param, &p_idx, mem[(*proc)->pc % MEM_SIZE], mem))
	{
		execute_error(*proc);
		return ;
	}
	val = lldi_calc(*proc, mem, param, &p_idx);
	(*proc)->reg[mem[p_idx[2]] - 1] = val;
	(*proc)->carry = val ? 0 : 1;
	(*proc)->pc = ((*proc)->pc + size) % MEM_SIZE;
	free(param);
}

/*
**	MAINTEST
**	see the four first instructions test_ldi.s to get an explanation

int		main(void)
{
	unsigned char	*mem = ft_memalloc(MEM_SIZE);
	unsigned char	var[2] = {0x06, 0x28};
	unsigned short	var_val = var[0];
	var_val = (var_val << 8) | var[1];
	unsigned char	txt[] = {\
		6, 0xa4, 0, 0, 0, 3, 0, 0, 0, 6,\
				  0x0b, 0x0e, 0xe4, var[0], var[1], 0, 0, 3, 3, 0x70,\
				  3, 0, 0x3d, 6, 0xa4, 0, 0, 0, 0x10, 0,\
				  0, 0, 0x11, 0x10, 6, 0xa4, 0, 0, 0, 0x0a,\
				  0, 0, 0, 5, 0x0f, 7, 0xa4, 0, 0, 0,\
				  0x18, 0, 0, 7, 0xf5, 0x0e, 7, 0xa4, 0, 0,\
				  0, 6, 0, 0, 0, 0x34, 0x0d\
	}; 

	//only the ten first bytes of golems binary are copied here
	unsigned char	golem[] = {\
		3, 0x50, 1,\
			7, 2, 0x90, 0, 0, 0, 0x30, 0x10, 2, 0x90,\
			1, 0, 0, 0, 2, 0x0b, 0x68, 2, 0, 0x26,\
			0, 0, 0x0b, 0x68, 7, 0, 0x1f, 0, 1, 0x0b,\
			0x68, 2, 0, 0, 0, 0x60, 0x0b, 0x68, 7, 0,\
			0, 0, 0x5a, 3, 0x70, 2, 0, 0x2a, 3, 0x70,\
			3, 0, 0x2b, 0x10, 0x40, 0x10, 0x10, 0x40, 0x10, 0x10,\
			0x40, 0x10, 1, 0, 0, 0, 2\
	};

	//unsigned char	*test = ft_memalloc(32);
	t_proc			*proc = ft_memalloc(sizeof(t_proc));
		
	write_on_mem(mem, 0, txt, 68);
	write_on_mem(mem, 2048, golem, 60);
	//ft_memset(test, 42, 31);
	//write_on_mem(mem, 511, test, 31);
	ft_printf("Initial conditions:\n");
	print_proc(proc);
	print_mem(mem, 68);
	ft_printf("-------------------\n\n");

	ft_printf("lldi %hu, %%0, r3\n", var_val);
	f_and(&proc, mem);
	f_lldi(&proc, mem);
	print_proc(proc);
	print_mem(mem, 68);
	ft_printf("golem @ mem[%d]\n", 2048);
	print_mem(&mem[2048], 64);
	ft_printf("-------------------\n\n");

	return (0);
}
*/
