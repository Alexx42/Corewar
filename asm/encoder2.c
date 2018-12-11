/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:21:28 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/06 13:37:48 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>
#include <string.h>
#include "libft.h"

void			big_endian_writer(uint32_t data, int out_fd, char size)
{
	int				i;
	unsigned char	octet;
	uint32_t		mask;

	i = 0;
	mask = 0xFF000000 >> (4 - size) * 8;
	while (i < size)
	{
		octet = (data & mask) >> ((size - 1) * 8);
		write(out_fd, &octet, 1);
		data = data << 8;
		i++;
	}
}

t_op			*get_op(char op_code)
{
	int			i;
	extern t_op	op_tab[];

	i = 0;
	while (i < 17)
	{
		if (op_tab[i].op_code == op_code)
			return (&op_tab[i]);
		i++;
	}
	return (NULL);
}

void			write_encoding_byte(t_param params[],
				char num_params, int out_fd)
{
	int		i;
	char	octet;
	char	type;

	i = 0;
	octet = 0;
	while (i < 4)
	{
		if (i < num_params)
		{
			if (params[i].type == T_REG)
				type = REG_CODE;
			else if (params[i].type == T_DIR)
				type = DIR_CODE;
			else if (params[i].type == T_IND)
				type = IND_CODE;
			octet = (octet << 2) + type;
		}
		else
			octet = octet << 2;
		i++;
	}
	write(out_fd, &octet, 1);
}
