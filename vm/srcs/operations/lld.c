/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:52:31 by acakste           #+#    #+#             */
/*   Updated: 2018/11/06 15:12:07 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "operations.h"

extern	t_opts g_opts;

/*
** modifies the carry
*/

int		lld_op(t_process *process, t_exc_instr *instr)
{
	uint64_t		reg_num;
	uint64_t		offset;
	unsigned char	*load_dst;
	unsigned char	flags;

	reg_num = convert_reg_uint(instr->params[1].mem, instr->params[1].len);
	if (reg_num > REG_NUMBER || reg_num == 0)
		return (0);
	if (instr->params[0].len == T_IND)
	{
		offset = convert_reg_uint(instr->params[0].mem, instr->params[1].len);
		load_dst = get_pc_moved(process->pc, offset, 0);
		memcpy_circle_src(process->reg[reg_num - 1], load_dst, REG_SIZE);
	}
	else
		ft_memcpy(process->reg[reg_num - 1], instr->params[0].mem, REG_SIZE);
	alu(process->reg[reg_num - 1], NULL, &flags, ALU_PASS);
	process->carry = (flags & ALU_EMPTY) ? 1 : 0;
	if (g_opts.vizualizer)
		print_carry(process->carry, "lld ");
	return (0);
}
