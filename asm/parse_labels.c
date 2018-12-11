/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:59:25 by acakste           #+#    #+#             */
/*   Updated: 2018/11/09 21:19:44 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

static int		is_label_char(char c)
{
	int	i;

	i = 0;
	while ((LABEL_CHARS[i] && c != LABEL_CHARS[i]))
		i++;
	return ((LABEL_CHARS[i]) ? 1 : 0);
}

static int		add_undef_label_ref(t_label_ref **label_ref,
				t_param *param, char *str, uint32_t offset)
{
	t_label_ref	*new;
	int			i;

	i = 0;
	new = (t_label_ref*)malloc(sizeof(t_label_ref));
	while (is_label_char(str[i]))
		i++;
	new->name = ft_strsub(str, 0, i);
	new->param = param;
	new->offset_instr = offset;
	new->next = NULL;
	if (!new)
		return (1);
	if (*label_ref)
		new->next = (*label_ref);
	(*label_ref) = new;
	return (0);
}

char			*ft_del_spaces(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (IS_WS(str[i]))
		i++;
	MCK(ret = (char *)malloc(sizeof(char) * ft_strlen(str) - i + 1), NULL);
	i = 0;
	while (str[i])
	{
		if (!IS_WS(str[i]))
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int				search_label(t_tokens *data, t_param *param,
				char *str, uint32_t offset)
{
	t_label_def	*curr;

	curr = data->labels.label_def;
	while (curr)
	{
		if (ft_strcmp(curr->name, str) == 0)
		{
			param->value = curr->value - offset;
			return (0);
		}
		curr = curr->next;
	}
	param->value = 0;
	return (add_undef_label_ref(&data->labels.label_ref, param, str, offset));
}

char			*check_label(char *line, t_label_def **label, uint32_t offset)
{
	int			i;
	t_label_def *lab;

	i = 0;
	while (is_label_char(line[i]))
		i++;
	if (line[i] == LABEL_CHAR)
	{
		lab = create_label_def();
		lab->name = (char *)malloc(sizeof(char) * (i + 1));
		ft_strncpy(lab->name, line, i);
		lab->name[i] = '\0';
		lab->value = offset;
		label_def_lst_add(label, lab);
		return (&line[i + 1]);
	}
	return (line);
}
