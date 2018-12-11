/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:21:51 by dprevost          #+#    #+#             */
/*   Updated: 2018/11/07 15:22:12 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static unsigned char *g_mem_start;

void			set_arena_mem_start(unsigned char *mem)
{
	g_mem_start = mem;
}

unsigned char	*get_mem_start(void)
{
	return (g_mem_start);
}
