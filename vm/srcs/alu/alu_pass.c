/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alu_pass.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 10:37:42 by acakste           #+#    #+#             */
/*   Updated: 2018/11/07 15:43:11 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alu.h"
#include "vm.h"

unsigned char	alu_pass(unsigned char *a, unsigned char *b,
	unsigned char **dst)
{
	int				i;
	unsigned char	flags;

	i = 0;
	flags = ALU_EMPTY;
	(void)b;
	(void)dst;
	while (i < REG_SIZE)
	{
		if (i == 0 && a[i])
			flags = flags | ALU_NEG;
		if (a[i])
			flags = flags & ~ALU_EMPTY;
		i++;
	}
	return (flags);
}
