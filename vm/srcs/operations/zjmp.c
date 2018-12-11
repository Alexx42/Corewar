/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:52:04 by acakste           #+#    #+#             */
/*   Updated: 2018/11/05 14:21:41 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "operations.h"

int		zjmp_op(t_process *process, t_exc_instr *instr)
{
	uint64_t val;

	if (!(process->carry))
	{
		move_pc(&process->pc, instr->instr_len, 0);
		return (0);
	}
	val = convert_reg_uint(((instr->params)[0]).mem, instr->params[0].len);
	move_pc(&(process->pc), (long long)val, 1);
	return (0);
}
