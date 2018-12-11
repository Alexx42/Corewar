/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:36:01 by acakste           #+#    #+#             */
/*   Updated: 2018/11/07 15:24:56 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void			move_pc(unsigned char **pc, long long len, char do_mod)
{
	uint32_t		distance;
	uint64_t		len_move;
	unsigned char	*mem_start;

	mem_start = get_mem_start();
	if (do_mod)
		len %= IDX_MOD;
	distance = *pc - mem_start;
	len_move = (uint64_t)len;
	*pc = mem_start + (distance + len_move) % MEM_SIZE;
}

unsigned char	*get_pc_moved(unsigned char *pc, long long len, char do_mod)
{
	unsigned char	*move;
	uint32_t		distance;
	uint64_t		len_move;
	unsigned char	*mem_start;

	mem_start = get_mem_start();
	if (do_mod)
		len = (len % IDX_MOD);
	distance = pc - mem_start;
	len_move = (uint64_t)len;
	move = mem_start + (distance + len_move) % MEM_SIZE;
	return (move);
}

void			*memcpy_circle_src(void *dst, const void *src, uint64_t len)
{
	unsigned char		*d;
	unsigned char		*s;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	while (len--)
	{
		*d = *s;
		d++;
		s = get_pc_moved(s, 1, 0);
	}
	return (dst);
}

void			*memcpy_circle_dst(void *dst, const void *src, uint64_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	while (len--)
	{
		*d = *s;
		d = get_pc_moved(d, 1, 0);
		s++;
	}
	return (dst);
}
