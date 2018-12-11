/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:51:59 by acakste           #+#    #+#             */
/*   Updated: 2018/11/06 15:14:16 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "operations.h"

extern	t_opts g_opts;

/*
** modifies the carry
*/

int		xor_op(t_process *process, t_exc_instr *instr)
{
	unsigned char	*reg_num1;
	unsigned char	*reg_num2;
	uint64_t		reg_num3;
	unsigned char	*res;
	unsigned char	flags;

	MCK(reg_num1 = get_mem(process, instr, 0, 1), 1);
	MCK(reg_num2 = get_mem(process, instr, 1, 1), 1);
	res = alu(reg_num1, reg_num2, &flags, ALU_XOR);
	free(reg_num1);
	free(reg_num2);
	MCK(reg_num3 = convert_reg_uint(instr->params[2].mem, REG_SIZE), 1);
	if (reg_num3 <= REG_NUMBER && reg_num3 > 0)
	{
		ft_memcpy(process->reg[reg_num3 - 1], res, REG_SIZE);
		process->carry = (flags & ALU_EMPTY) ? 1 : 0;
	}
	free(res);
	if (g_opts.vizualizer)
		print_carry(process->carry, "xor ");
	return (0);
}
