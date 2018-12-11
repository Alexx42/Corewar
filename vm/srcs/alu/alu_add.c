/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alu_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 08:11:40 by acakste           #+#    #+#             */
/*   Updated: 2018/11/07 15:47:13 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alu.h"

static t_alu_res	half_adder(unsigned char a, unsigned char b)
{
	t_alu_res	res;

	res.d = (a & 1) ^ (b & 1);
	res.c = (a & 1) & (b & 1);
	return (res);
}

t_alu_res			full_adder(unsigned char a, unsigned char b,
	unsigned char c)
{
	t_alu_res	sub_res;
	t_alu_res	res;

	sub_res = half_adder(a, b);
	res = half_adder(sub_res.d, c);
	res.c = (sub_res.c & 1) | (res.c & 1);
	return (res);
}

t_alu_res			eight_bit_adder(unsigned char a, unsigned char b,
	unsigned char c)
{
	t_alu_res		res;
	t_alu_res		sub_res;
	int				i;

	i = 0;
	res.c = c;
	res.d = 0;
	ft_bzero(&sub_res, sizeof(t_alu_res));
	while (i < 8)
	{
		sub_res = full_adder(a, b, sub_res.c);
		res.d = res.d | (sub_res.d << i);
		a = a >> 1;
		b = b >> 1;
		i++;
	}
	res.c = sub_res.c;
	return (res);
}

/*
**	always assume that a, b and dst are size REG_SIZE. (Store %1, in tmp reg)
*/

unsigned char		mem_addr_little_end(unsigned char *a, unsigned char *b,
	unsigned char **dst, uint64_t size)
{
	size_t		i;
	t_alu_res	res;

	i = 0;
	res.c = 0;
	if ((*dst = ft_memalloc(REG_SIZE)) == NULL)
		return (ALU_ERROR);
	while (i < size)
	{
		res = eight_bit_adder(a[i], b[i], res.c);
		(*dst)[i] = res.d;
		i++;
	}
	if (res.c)
		return (ALU_CARRY | ALU_OVERFLOW | alu_pass(*dst, NULL, NULL));
	return (alu_pass(*dst, NULL, NULL));
}

/*
**	always assume that a, b and dst are size REG_SIZE. (Store %1, in tmp reg)
*/

unsigned char		mem_addr_big_end(unsigned char *a, unsigned char *b,
	unsigned char **dst)
{
	int			i;
	t_alu_res	res;

	i = REG_SIZE - 1;
	res.c = 0;
	if ((*dst = ft_memalloc(REG_SIZE)) == NULL)
		return (ALU_ERROR);
	while (i >= 0)
	{
		res = eight_bit_adder(a[i], b[i], res.c);
		(*dst)[i] = res.d;
		i--;
	}
	if (res.c)
		return (ALU_CARRY | ALU_OVERFLOW | alu_pass(*dst, NULL, NULL));
	return (alu_pass(*dst, NULL, NULL));
}
