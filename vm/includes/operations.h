/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 19:35:40 by acakste           #+#    #+#             */
/*   Updated: 2018/11/12 08:22:13 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H
# include "vm.h"

/*
**	srcs/operations/
*/

int				add_op(t_process *process, t_exc_instr *instr);
int				aff_op(t_process *process, t_exc_instr *instr);
int				and_op(t_process *process, t_exc_instr *instr);
int				fork_op(t_process *process, t_exc_instr *instr, t_process **p);
int				ld_op(t_process *process, t_exc_instr *instr);
int				lld_op(t_process *process, t_exc_instr *instr);
int				ldi_op(t_process *process, t_exc_instr *instr);
int				lfork_op(t_process *process, t_exc_instr *instr, t_process **p);
int				live_op(t_process *process, t_clock *clock);
int				lldi_op(t_process *process, t_exc_instr *instr);
int				or_op(t_process *process, t_exc_instr *instr);
int				st_op(t_process *process, t_exc_instr *instr);
int				sti_op(t_process *process, t_exc_instr *instr);
int				sub_op(t_process *process, t_exc_instr *instr);
int				xor_op(t_process *process, t_exc_instr *instr);
int				zjmp_op(t_process *process, t_exc_instr *instr);

unsigned char	*get_mem(t_process *process, t_exc_instr *instr,
	int param_num, char do_mod);
unsigned char	*get_short_mem(t_process *process, t_exc_instr *instr,
	int param_num, char do_mod);

/*
**	operations/help_op.c
**	some useful function for operations
*/
void			*take_size(void *mem, size_t mem_size);
uint64_t		convert_reg_uint(unsigned char *mem, size_t mem_len);

#endif
