/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 13:00:06 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/12 07:11:58 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "operations.h"

int		live_op(t_process *process, t_clock *clock)
{
	unsigned char	*src;
	unsigned char	*tmp;
	uint64_t		play_num;

	src = get_pc_moved(process->pc, 1, 0);
	MCK(tmp = ft_memalloc(REG_SIZE), 1);
	memcpy_circle_src(tmp, src, REG_SIZE);
	play_num = convert_reg_uint(tmp, REG_SIZE);
	process->lived_curr_period = 1;
	clock->lives_curr_period++;
	if (play_num * -1 > MAX_PLAYERS || play_num == 0)
		return (1);
	(clock->last_live)[play_num * -1 - 1] = clock->num_cycles;
	return (0);
}
