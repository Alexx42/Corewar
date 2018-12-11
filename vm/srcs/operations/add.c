/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:51:46 by acakste           #+#    #+#             */
/*   Updated: 2018/11/12 07:09:21 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "vm.h"
#include "alu.h"

/*
** modifies the carry
*/

int	add_op(t_process *process, t_exc_instr *instr)
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
	result = alu(process->reg[reg_num1 - 1],
		process->reg[reg_num2 - 1], &flags, ALU_ADD);
	ft_memcpy(process->reg[reg_num3 - 1], result, REG_SIZE);
	free(result);
	process->carry = (flags & ALU_EMPTY) ? 1 : 0;
	print_carry(process->carry, "add ");
	return (0);
}
