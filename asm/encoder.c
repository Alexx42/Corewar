/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:00:04 by acakste           #+#    #+#             */
/*   Updated: 2018/11/09 18:38:03 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>
#include <string.h>
#include "libft.h"

static int	write_params(t_param params[], char num_params,
			t_op *op, int out_fd)
{
	int		i;
	char	write_size;

	i = 0;
	while (i < num_params)
	{
		if (op->shorten_dir_len && params[i].type == T_DIR)
			write_size = T_IND;
		else if (params[i].type == T_REG)
			write_size = T_REG;
		else if (params[i].type == T_DIR)
			write_size = T_DIR;
		else if (params[i].type == T_IND)
			write_size = T_IND;
		big_endian_writer(params[i].value, out_fd, write_size);
		i++;
	}
	return (0);
}

int			asm_encode_instr(t_instr *instr, int out_fd)
{
	t_op		*op;

	write(out_fd, &instr->op_code, 1);
	op = get_op(instr->op_code);
	if (op->encoding_byte)
		write_encoding_byte(instr->param, instr->num_params, out_fd);
	write_params(instr->param, instr->num_params, op, out_fd);
	return (0);
}

static int	write_str_fixed_len(char *str, int out_len, int out_fd)
{
	int		str_len;
	char	*empty_str;

	if (!str)
		return (1);
	str_len = ft_strlen(str);
	write(out_fd, str, str_len);
	empty_str = ft_strnew(out_len - str_len);
	if (!empty_str)
		return (1);
	write(out_fd, empty_str, out_len - str_len);
	free(empty_str);
	return (0);
}

/*
**	Writing the following things: magic, PROG_NAME_LENGTH bytes of prog_name,
**	4 empty bytes, 4 bytes bytes prog_len, COMMENT_LENGTH bytes of comment,
**	4 empty bytes. WE SHOULD CHECK IF PROG_LEN CAN FIT IN 2 BYTES
*/

int			asm_encode_header(t_header *header, int out_fd)
{
	big_endian_writer(header->magic, out_fd, 4);
	if (write_str_fixed_len(header->prog_name, PROG_NAME_LENGTH, out_fd))
		return (1);
	big_endian_writer(0, out_fd, 4);
	big_endian_writer(header->prog_size, out_fd, 4);
	if (write_str_fixed_len(header->comment, COMMENT_LENGTH, out_fd))
		return (1);
	big_endian_writer(0, out_fd, 4);
	return (0);
}

int			asm_encoder(t_header *header, t_instr *instructs, int out_fd)
{
	t_instr	*curr;

	if (asm_encode_header(header, out_fd))
		return (1);
	curr = instructs;
	while (curr)
	{
		asm_encode_instr(curr, out_fd);
		curr = curr->next;
	}
	return (0);
}
