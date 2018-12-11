/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:13:01 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/07 15:20:16 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			change_endianness(unsigned char *mem, size_t len)
{
	int				s;
	int				e;
	unsigned char	tmp;

	s = 0;
	e = len - 1;
	while (s < e)
	{
		tmp = mem[s];
		mem[s] = mem[e];
		mem[e] = tmp;
		s++;
		e--;
	}
}

unsigned char	*mem_to_reg(unsigned char *mem, size_t len)
{
	int				i;
	int				j;
	unsigned char	*new_reg;
	unsigned char	*mem_cpy;

	if ((mem_cpy = (unsigned char*)malloc(len)) == NULL)
		return (NULL);
	ft_memcpy(mem_cpy, mem, len);
	change_endianness(mem_cpy, len);
	new_reg = (unsigned char*)malloc(REG_SIZE);
	ft_bzero(new_reg, REG_SIZE);
	i = REG_SIZE - 1;
	j = len - 1;
	while (i >= 0)
	{
		if (j >= 0)
			new_reg[i] = mem_cpy[j];
		i--;
		j--;
	}
	free(mem_cpy);
	return (new_reg);
}

int				extend_reg(unsigned char *mem, int offset)
{
	offset--;
	while (offset >= 0)
	{
		mem[offset] = 0xFF;
		offset--;
	}
	return (0);
}
