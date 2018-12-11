/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 10:28:05 by acakste           #+#    #+#             */
/*   Updated: 2018/11/12 07:16:35 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alu.h"
#include "libft.h"
#include "ft_printf.h"

static	t_alu_op g_alu_op[NUM_ALU_OP + 1] = {
	{ALU_ADD, &mem_circuit_big_end},
	{ALU_SUB, &mem_circuit_big_end},
	{ALU_PASS, &alu_pass},
	{ALU_AND, &alu_and},
	{ALU_OR, &alu_or},
	{ALU_XOR, &alu_xor},
	{0, 0}
};

unsigned char	(*get_op(char op_code))()
{
	int	i;

	i = 0;
	while (i < NUM_ALU_OP)
	{
		if (op_code == g_alu_op[i].op_code)
			return (g_alu_op[i].f);
		i++;
	}
	ft_putstr("ERROR\n");
	return (NULL);
}

unsigned char	*alu_neg(unsigned char *b)
{
	int				i;
	unsigned char	*b_neg;

	MCK(b_neg = ft_memalloc(REG_SIZE), NULL);
	i = 0;
	while (i < REG_SIZE)
	{
		b_neg[i] = ~b[i];
		i++;
	}
	return (b_neg);
}

unsigned char	*alu_twos_comp(unsigned char *b)
{
	unsigned char	*incr;
	unsigned char	*b_neg;
	unsigned char	*res;

	b_neg = alu_neg(b);
	MCK(incr = ft_memalloc(REG_SIZE), NULL);
	incr[REG_SIZE - 1] = 1;
	mem_circuit_big_end(b_neg, incr, &res);
	free(b_neg);
	free(incr);
	return (res);
}

unsigned char	*alu(unsigned char *a, unsigned char *b,
	unsigned char *flags, char op_code)
{
	unsigned char	(*f)();
	unsigned char	*dst;
	unsigned char	flag_store;

	f = get_op(op_code);
	flag_store = 0;
	dst = NULL;
	if (f == NULL)
	{
		if (flags)
			*flags = ALU_ERROR;
		return (NULL);
	}
	if (op_code == ALU_SUB)
		b = alu_twos_comp(b);
	flag_store += f(a, b, &dst);
	if (op_code == ALU_SUB)
		free(b);
	if (flags)
		*flags = flag_store;
	return (dst);
}
