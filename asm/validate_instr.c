/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_instr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 19:40:19 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/09 15:37:13 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "libft.h"

int				set_undef_refs(t_label_ref *label_ref, t_label_def *label_def)
{
	t_label_ref	*ref;
	t_label_def	*def;

	ref = label_ref;
	while (ref)
	{
		if ((def = label_def_lst_find(label_def, ref->name)) == NULL)
			return (1);
		ref->param->value += def->value - ref->offset_instr;
		ref = ref->next;
	}
	return (0);
}

static int		get_param_size(char type, char shorten_dir_len)
{
	if (type & REG_CODE)
		return (T_REG);
	else if (type & IND_CODE)
		return (T_IND);
	else if (type & T_DIR)
		return (shorten_dir_len ? T_IND : T_DIR);
	return (0);
}

static int		validate_params(t_op *op, t_instr *instr)
{
	int			i;
	uint32_t	size;

	i = 0;
	size = 1;
	if (instr->num_params != op->num_params)
		return (syntax_error("invalid number of parameters"));
	while (i < instr->num_params)
	{
		if ((instr->param[i].type & op->valid_params[i]) == 0)
			return (syntax_error("invalid parameter type"));
		size += get_param_size(instr->param[i].type, op->shorten_dir_len);
		i++;
	}
	if (op->encoding_byte)
		size++;
	instr->out_offset = size;
	return (0);
}

int				validate_instr(t_instr *i)
{
	extern	t_op	op_tab[];
	t_op			op;

	if (i->op_code > 16)
		return (error("invalid op code"));
	op = op_tab[(int)i->op_code - 1];
	if (validate_params(&op, i))
		return (1);
	return (0);
}
