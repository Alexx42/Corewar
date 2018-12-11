/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 09:31:04 by acakste           #+#    #+#             */
/*   Updated: 2018/11/06 12:58:48 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALU_H
# define ALU_H
# include <stdlib.h>
# include <stdio.h>
# include <op.h>
# include <vm.h>
# define NUM_ALU_OP 6
# define ALU_ADD 1
# define ALU_SUB 2
# define ALU_PASS 3
# define ALU_AND 4
# define ALU_OR 5
# define ALU_XOR 6
# define ALU_WHAT 4
# define ALU_OVERFLOW 1
# define ALU_NEG 2
# define ALU_CARRY 4
# define ALU_ERROR 8
# define ALU_EMPTY 16

typedef struct	s_alu_op
{
	char			op_code;
	unsigned char	(*f)();
}				t_alu_op;

typedef struct	s_alu_res
{
	unsigned char	d;
	unsigned char	c;
}				t_alu_res;

/*
** could add controlled inverter instead of having half and full funcs.
*/

/*
**	alu_add.c
*/
unsigned char	mem_addr_big_end(unsigned char *a, unsigned char *b,
					unsigned char **dst);
unsigned char	mem_addr_little_end(unsigned char *a, unsigned char *b,
					unsigned char **dst, uint64_t size);

/*
**	ALU OPERATIONS (in srcs/alu/<func_name>.c)
*/
unsigned char	alu_pass(unsigned char *a, unsigned char *b,
	unsigned char **dst);
unsigned char	alu_and(unsigned char *a, unsigned char *b,
	unsigned char **dst);
unsigned char	alu_or(unsigned char *a, unsigned char *b,
	unsigned char **dst);
unsigned char	alu_xor(unsigned char *a, unsigned char *b,
	unsigned char **dst);
unsigned char	mem_circuit_big_end(unsigned char *a, unsigned char *b,
	unsigned char **dst);

/*
**	alu_sub.c
*/
unsigned char	mem_sub_big_end(unsigned char *a, unsigned char *b,
					unsigned char **dst);
unsigned char	mem_sub_little_end(unsigned char *a, unsigned char *b,
					unsigned char **dst, uint64_t size);

/*
**	alu.c
*/
unsigned char	*alu(unsigned char *a, unsigned char *b,
	unsigned char *flags, char op_code);

#endif
