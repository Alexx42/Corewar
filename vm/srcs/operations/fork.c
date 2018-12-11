/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:52:28 by acakste           #+#    #+#             */
/*   Updated: 2018/11/12 08:20:29 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "operations.h"

static int	fork_process(t_process *curr, t_process **processes)
{
	t_process	*new;

	new = ft_memalloc(sizeof(t_process));
	if (!new)
		return (1);
	ft_memcpy(new, curr, sizeof(t_process));
	new->next = (*processes);
	new->prev = NULL;
	new->next->prev = new;
	*processes = new;
	return (0);
}

/*
**does not modify the carry
*/

int			fork_op(t_process *p, t_exc_instr *instr, t_process **processes)
{
	uint64_t	value;

	if (fork_process(p, processes))
		return (1);
	value = convert_reg_uint(instr->params[0].mem, instr->params[0].len);
	(*processes)->old_pc = (*processes)->pc;
	move_pc(&(*processes)->pc, value, 1);
	return (0);
}
