/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_get_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:41:52 by dprevost          #+#    #+#             */
/*   Updated: 2018/11/12 07:26:22 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_encoding_param(unsigned char check, unsigned char valid_param)
{
	if ((check & 3) == IND_CODE)
		return ((T_IND & valid_param) ? 0 : 1);
	else if ((check & 3) == DIR_CODE)
		return ((T_DIR & valid_param) ? 0 : 1);
	else if ((check & 3) == REG_CODE)
		return ((T_REG & valid_param) ? 0 : 1);
	return (1);
}

int		get_param_len(unsigned char check, t_mem *param,
	char shorten_dir_len, char num_params)
{
	int	j;

	j = 4;
	while (--j >= 0)
	{
		if (j < (int)num_params)
		{
			if ((check & 3) == IND_CODE)
				param[j].len = T_IND;
			else if ((check & 3) == DIR_CODE)
				param[j].len = (shorten_dir_len) ? T_IND : T_DIR;
			else if ((check & 3) == REG_CODE)
				param[j].len = T_REG;
			else
				param[j].len = 0;
			param[j].type = check & 3;
		}
		else
		{
			param[j].len = 0;
			param[j].type = 0;
		}
		check = check >> 2;
	}
	return (0);
}

int		check_encoding_byte(unsigned char *curr, t_op op, t_mem *param)
{
	int				j;
	unsigned char	check;

	j = 3;
	check = *curr;
	get_param_len(check, param, op.shorten_dir_len, op.num_params);
	while (j >= 0)
	{
		if (j < op.num_params)
			if (check_encoding_param(check, op.valid_params[j]))
				return (1);
		j--;
		check = check >> 2;
	}
	return (0);
}

int		load_params(unsigned char *pc, t_mem *param, int *i)
{
	int	j;
	int	offset;

	j = 0;
	while ((param)[j].len != 0 && j < 4)
	{
		param[j].mem = (unsigned char*)malloc(REG_SIZE);
		if (!param[j].mem)
			return (1);
		ft_bzero((void*)param[j].mem, REG_SIZE);
		offset = REG_SIZE - (param)[j].len;
		memcpy_circle_src((void*)&(param)[j].mem[offset],
			get_pc_moved(pc, *i, 0), (param)[j].len);
		if (param[j].mem[offset] & 1 << 7)
			extend_reg(param[j].mem, offset);
		*i += param[j].len;
		j++;
	}
	return (0);
}

int		set_param_len(t_mem param[4], t_op op)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (i < op.num_params)
		{
			if (op.shorten_dir_len && op.valid_params[i] & T_DIR)
				param[i].len = T_IND;
			else
				param[i].len = T_DIR;
			param[i].type = DIR_CODE;
		}
		else
		{
			param[i].len = 0;
			param[i].type = 0;
		}
		i++;
	}
	return (0);
}
