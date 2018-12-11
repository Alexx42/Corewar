/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:52:18 by acakste           #+#    #+#             */
/*   Updated: 2018/11/12 08:16:01 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "operations.h"

extern	t_opts g_opts;

/*
** does not modify the carry
*/

int		sti_op(t_process *process, t_exc_instr *instr)
{
	unsigned char	*param2;
	unsigned char	*param3;
	unsigned char	*sum;
	uint64_t		dst_offset;
	uint64_t		reg_num;

	reg_num = convert_reg_uint(instr->params[0].mem, instr->params[0].len);
	if (reg_num > REG_NUMBER || reg_num == 0)
		return (0);
	MCK(param2 = get_mem(process, instr, 1, 1), 0);
	MCK(param3 = get_mem(process, instr, 2, 1), 0);
	sum = alu(param2, param3, NULL, ALU_ADD);
	dst_offset = convert_reg_uint(sum, REG_SIZE);
	free(sum);
	mvprintw(80, 30, "STI");
	memcpy_circle_dst(get_pc_moved(process->pc, dst_offset, 1),
		process->reg[reg_num - 1], REG_SIZE);
	if (g_opts.vizualizer)
	{
		disp_change_dst(get_pc_moved(process->pc, dst_offset, 1),
			REG_SIZE, process->player_num * -1);
		mvprintw(80, 30, "   ");
	}
	return (0);
}
