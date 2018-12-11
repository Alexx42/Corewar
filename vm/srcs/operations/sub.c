/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:51:50 by acakste           #+#    #+#             */
/*   Updated: 2018/11/06 15:14:00 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "operations.h"

extern	t_opts g_opts;

/*
** modifies the carry
*/

int		sub_op(t_process *process, t_exc_instr *instr)
{
	unsigned char	*result;
	unsigned char	flags;
	uint64_t		reg_num1;
	uint64_t		reg_num2;
	uint64_t		reg_num3;

	flags = 0;
	reg_num1 = convert_reg_uint(instr->params[0].mem, instr->params[0].len);
	reg_num2 = convert_reg_uint(instr->params[1].mem, instr->params[1].len);
	reg_num3 = convert_reg_uint(instr->params[2].mem, instr->params[2].len);
	if (reg_num1 > REG_NUMBER || reg_num1 == 0 || reg_num2 > REG_NUMBER ||
		reg_num2 == 0 || reg_num3 > REG_NUMBER || reg_num3 == 0)
		return (0);
	result = alu(process->reg[reg_num1 - 1], process->reg[reg_num2 - 1],
		&flags, ALU_SUB);
	ft_memcpy(process->reg[reg_num3 - 1], result, REG_SIZE);
	free(result);
	process->carry = (flags & ALU_EMPTY) ? 1 : 0;
	if (g_opts.vizualizer)
		print_carry(process->carry, "sub ");
	return (0);
}
