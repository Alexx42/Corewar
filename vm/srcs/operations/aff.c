/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:52:48 by acakste           #+#    #+#             */
/*   Updated: 2018/11/10 13:15:37 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "vm.h"
#include "ft_printf.h"

extern	t_opts g_opts;

/*
**does not modify the carry
*/

int		aff_op(t_process *process, t_exc_instr *instr)
{
	uint64_t	reg_num;

	reg_num = convert_reg_uint(instr->params[0].mem, instr->params[0].len);
	if (reg_num > REG_NUMBER || reg_num == 0)
		return (0);
	if (g_opts.vizualizer)
		disp_aff(process->reg[reg_num - 1][REG_SIZE - 1]);
	else if (g_opts.aff)
		ft_printf("AFF = %c\n", (char)process->reg[reg_num - 1][REG_SIZE - 1]);
	return (0);
}
