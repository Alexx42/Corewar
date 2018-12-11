/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 19:38:09 by dprevost          #+#    #+#             */
/*   Updated: 2018/11/12 07:09:45 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "vm.h"

void			*take_size(void *mem, size_t mem_size)
{
	int				i;
	unsigned char	*dst;
	unsigned char	*src;

	dst = (unsigned char*)ft_memalloc(mem_size + 1);
	dst[mem_size + 1] = '\0';
	src = (unsigned char*)mem;
	i = 0;
	while (src[i])
	{
		dst[mem_size - i] = src[REG_SIZE - i];
		i++;
	}
	return ((void*)dst);
}

unsigned char	*get_short_mem(t_process *process,
	t_exc_instr *instr, int param_num, char do_mod)
{
	unsigned char	*res;
	uint64_t		num;

	MCK(res = ft_memalloc(REG_SIZE), NULL);
	if (instr->params[param_num].type == REG_CODE)
	{
		num = convert_reg_uint(instr->params[param_num].mem,
			instr->params[param_num].len);
		if (num >= REG_NUMBER)
			return (NULL);
		ft_memcpy(res, process->reg[num - 1], REG_SIZE);
		return (res);
	}
	else if (instr->params[param_num].type == IND_CODE)
	{
		num = convert_reg_uint(instr->params[param_num].mem,
			instr->params[param_num].len);
		return (memcpy_circle_src(res, get_pc_moved(process->pc, num, do_mod),
			IND_SIZE));
	}
	else if (instr->params[param_num].type == DIR_CODE)
		return (ft_memcpy(res, instr->params[param_num].mem, REG_SIZE));
	return (NULL);
}

unsigned char	*get_mem(t_process *process, t_exc_instr *instr,
	int param_num, char do_mod)
{
	unsigned char	*res;
	uint64_t		num;

	MCK(res = ft_memalloc(REG_SIZE), NULL);
	if (instr->params[param_num].type == REG_CODE)
	{
		num = convert_reg_uint(instr->params[param_num].mem,
			instr->params[param_num].len);
		if (num > REG_NUMBER || num == 0)
			return (NULL);
		ft_memcpy(res, process->reg[num - 1], REG_SIZE);
		return (res);
	}
	else if (instr->params[param_num].type == IND_CODE)
	{
		num = convert_reg_uint(instr->params[param_num].mem,
			instr->params[param_num].len);
		memcpy_circle_src(res, get_pc_moved(process->pc, num, do_mod),
			REG_SIZE);
		return (res);
	}
	else if (instr->params[param_num].type == DIR_CODE)
		return (ft_memcpy(res, instr->params[param_num].mem, REG_SIZE));
	return (NULL);
}

uint64_t		convert_reg_uint(unsigned char *mem, size_t mem_len)
{
	int				i;
	int				j;
	unsigned char	*dst;
	unsigned char	neg;
	uint64_t		dst_num;

	dst = (unsigned char*)&dst_num;
	ft_bzero(dst, 8);
	if (mem_len > REG_SIZE)
		return (0);
	neg = (mem[REG_SIZE - mem_len]) & (1 << 7) ? 1 : 0;
	i = 7;
	j = REG_SIZE - 1;
	while (i >= 0)
	{
		if (j >= 0)
			dst[i] = mem[j];
		else if (neg)
			dst[i] = 0xFF;
		j--;
		i--;
	}
	change_endianness(dst, 8);
	return (dst_num);
}
