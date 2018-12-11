/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:40:51 by acakste           #+#    #+#             */
/*   Updated: 2018/11/09 15:37:02 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_instr		*create_instr(void)
{
	t_instr *instr;

	MCK(instr = (t_instr *)malloc(sizeof(t_instr)), NULL);
	instr->op_code = 0;
	instr->out_offset = 0;
	instr->next = NULL;
	return (instr);
}

void		instr_lst_add(t_instr **end, t_instr *new)
{
	if (!end)
		return ;
	if (*end)
		(*end)->next = new;
	*end = new;
}

t_label_def	*create_label_def(void)
{
	t_label_def	*new;

	new = (t_label_def*)malloc(sizeof(t_label_def));
	if (!new)
		return (NULL);
	new->name = NULL;
	new->value = 0;
	new->next = NULL;
	return (new);
}

void		label_def_lst_add(t_label_def **end, t_label_def *new)
{
	if (!end)
		return ;
	new->next = *end;
	(*end) = new;
}

t_label_def	*label_def_lst_find(t_label_def *label_def, char *name)
{
	t_label_def	*def;

	def = label_def;
	while (def)
	{
		if (ft_strcmp(def->name, name) == 0)
			return (def);
		def = def->next;
	}
	return (NULL);
}
