/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alu_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 15:50:23 by acakste           #+#    #+#             */
/*   Updated: 2018/11/03 15:50:24 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alu.h"
#include "vm.h"

unsigned char	alu_or(unsigned char *a, unsigned char *b, unsigned char **dst)
{
	int				i;
	unsigned char	flags;

	MCK(*dst = ft_memalloc(REG_SIZE), ALU_ERROR);
	i = 0;
	flags = ALU_EMPTY;
	while (i < REG_SIZE)
	{
		(*dst)[i] = a[i] | b[i];
		if (flags & ALU_EMPTY && (*dst)[i])
			flags = flags & ~ALU_EMPTY;
		i++;
	}
	return (flags);
}
