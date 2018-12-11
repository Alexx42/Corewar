/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:52:07 by acakste           #+#    #+#             */
/*   Updated: 2018/11/07 11:16:21 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "vm.h"

/*
** does not modify the carry!! PDF is wrong!
*/

int		ldi_op(t_process *process, t_exc_instr *instr)
{
	uint64_t		reg_num;
	unsigned char	*param1;
	unsigned char	*param2;
	unsigned char	*result;
	unsigned char	*load_dst;

	reg_num = convert_reg_uint(instr->params[2].mem, instr->params[2].len);
	if (reg_num > REG_NUMBER || reg_num == 0)
		return (0);
	MCK(param1 = get_mem(process, instr, 0, 1), 1);
	MCK(param2 = get_mem(process, instr, 1, 0), 1);
	result = alu(param1, param2, NULL, ALU_ADD);
	load_dst = get_pc_moved(process->pc, convert_reg_uint(result, REG_SIZE), 1);
	memcpy_circle_src(process->reg[reg_num - 1], load_dst, REG_SIZE);
	free(result);
	return (0);
}
