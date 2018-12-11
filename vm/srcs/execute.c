/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:47:06 by acakste           #+#    #+#             */
/*   Updated: 2018/11/12 08:18:42 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include <operations.h>

static	t_op_fn	g_op_fn[17 + 1] = {
	{1, &live_op}, {2, &ld_op}, {3, &st_op}, {4, &add_op}, {5, &sub_op},
	{6, &and_op}, {7, &or_op}, {8, &xor_op}, {9, &zjmp_op}, {10, &ldi_op},
	{11, &sti_op}, {12, &fork_op}, {13, &lld_op}, {14, &lldi_op},
	{15, &lfork_op}, {16, &aff_op}, {0, 0}
};

int		read_params(t_process *process, t_mem *param, int *i, t_op op)
{
	unsigned char	*curr;
	extern	t_opts	g_opts;

	if (op.encoding_byte)
	{
		curr = get_pc_moved(process->pc, *i, 0);
		if (check_encoding_byte(curr, op, param))
		{
			process->old_pc = process->pc;
			move_pc(&process->pc, 2 + param[0].len + param[1].len
				+ param[2].len + param[3].len, 0);
			return (1);
		}
		(*i)++;
	}
	else
		set_param_len(param, op);
	return (load_params(process->pc, param, i));
}

int		read_instruct(t_process *process, t_exc_instr *instr)
{
	extern	t_op	op_tab[];
	t_op			op;
	int				i;

	i = 0;
	if (process->timeout == 0)
	{
		if (process->pc[0] > 16 || process->pc[0] <= 0)
		{
			instr->op_code = ERROR_OP_CODE;
			return (0);
		}
		op = op_tab[process->pc[0] - 1];
		ft_bzero(instr, sizeof(t_exc_instr));
		instr->op_code = op.op_code;
		process->timeout = op.num_cycles;
	}
	return (0);
}

int		exec_instruct(t_process *process, t_clock *clock,
	t_exc_instr *instr, t_process **processes)
{
	t_op_fn			op_fn;
	int				i;
	extern t_op		op_tab[];
	extern t_opts	g_opts;

	if (instr->op_code == ERROR_OP_CODE)
	{
		process->old_pc = process->pc;
		move_pc(&process->pc, 1, 0);
		return (0);
	}
	i = 1;
	if (read_params(process, instr->params, &i, op_tab[instr->op_code - 1]))
		return (0);
	instr->instr_len = i;
	chose_op(process, clock, instr, &op_fn);
	if (instr->op_code == 15 || instr->op_code == 12)
		op_fn.func(process, instr, processes);
	if (instr->op_code != 9)
		move_pc(&process->pc, instr->instr_len, 0);
	return (0);
}

void	chose_op(t_process *process, t_clock *clock,
					t_exc_instr *instr, t_op_fn *op_fn)
{
	process->old_pc = process->pc;
	*op_fn = g_op_fn[instr->op_code - 1];
	if (instr->op_code == 1)
		op_fn->func(process, clock);
	if (instr->op_code != 15 && instr->op_code != 12)
		op_fn->func(process, instr);
}
