/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alu_xor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 15:50:26 by acakste           #+#    #+#             */
/*   Updated: 2018/11/03 16:07:58 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alu.h"
#include "vm.h"

unsigned char	alu_xor(unsigned char *a, unsigned char *b, unsigned char **dst)
{
	int				i;
	unsigned char	flags;

	MCK(*dst = ft_memalloc(REG_SIZE), ALU_ERROR);
	i = 0;
	flags = ALU_EMPTY;
	while (i < REG_SIZE)
	{
		(*dst)[i] = a[i] ^ b[i];
		if (flags & ALU_EMPTY && (*dst)[i])
			flags = flags & ~ALU_EMPTY;
		i++;
	}
	return (flags);
}
