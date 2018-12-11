/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:52:37 by acakste           #+#    #+#             */
/*   Updated: 2018/11/07 11:17:43 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "operations.h"

extern	t_opts g_opts;

/*
** modifies the carry
** BASED ON ldi 04/11/18
*/

int		lldi_op(t_process *process, t_exc_instr *instr)
{
	uint64_t		reg_num;
	unsigned char	*param1;
	unsigned char	*param2;
	unsigned char	*result;
	unsigned char	flags;

	reg_num = convert_reg_uint(instr->params[2].mem, instr->params[2].len);
	if (reg_num > REG_NUMBER || reg_num == 0)
		return (0);
	MCK(param1 = get_mem(process, instr, 0, 0), 1);
	MCK(param2 = get_mem(process, instr, 1, 0), 1);
	result = alu(param1, param2, &flags, ALU_ADD);
	memcpy_circle_src(process->reg[reg_num - 1],
		get_pc_moved(process->pc, convert_reg_uint(result, REG_SIZE), 0),
		REG_SIZE);
	free(result);
	alu(process->reg[reg_num - 1], NULL, &flags, ALU_PASS);
	process->carry = (flags & ALU_EMPTY) ? 1 : 0;
	if (g_opts.vizualizer)
		print_carry(process->carry, "lldi");
	return (0);
}
