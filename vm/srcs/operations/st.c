/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:51:41 by acakste           #+#    #+#             */
/*   Updated: 2018/11/06 15:13:18 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "operations.h"

extern	t_opts g_opts;

/*
** does not modify the carry
*/

int		st_op(t_process *process, t_exc_instr *instr)
{
	uint64_t		reg_src;
	uint64_t		offset;
	unsigned char	*load_dst;
	uint64_t		reg_dst;

	reg_src = convert_reg_uint(instr->params[0].mem, instr->params[0].len);
	if (reg_src > REG_NUMBER || reg_src == 0)
		return (0);
	if (instr->params[1].len == T_IND)
	{
		offset = convert_reg_uint(instr->params[1].mem, instr->params[1].len);
		load_dst = get_pc_moved(process->pc, offset, 1);
		memcpy_circle_dst(load_dst, process->reg[reg_src - 1], REG_SIZE);
		if (g_opts.vizualizer)
			disp_change_dst(load_dst, REG_SIZE, process->player_num * -1);
	}
	else
	{
		reg_dst = convert_reg_uint(instr->params[1].mem, instr->params[1].len);
		if (reg_dst > REG_NUMBER || reg_dst == 0)
			return (0);
		ft_memcpy(process->reg[reg_dst - 1], process->reg[reg_src - 1],
			REG_SIZE);
	}
	return (0);
}
