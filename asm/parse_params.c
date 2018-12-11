/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:56:43 by acakste           #+#    #+#             */
/*   Updated: 2018/11/06 21:40:52 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*set_param_type(t_param *param, char *str)
{
	if (*str == 'r')
		param->type = T_REG;
	else if (*str == DIRECT_CHAR)
	{
		param->type = T_DIR;
		str++;
	}
	else if (*str == LABEL_CHAR || (*str >= '0' && *str <= '9') || *str == '-')
		param->type = T_IND;
	else
		return (NULL);
	return (str);
}

static int	get_param_value(char *str, t_param *param)
{
	int	i;

	if (*str == 'r')
	{
		param->value = ft_atoi(str + 1);
		if (param->value > REG_NUMBER || param->value == 0)
			return (1);
		return (0);
	}
	i = 0;
	if (str[i] == '-')
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
		i++;
	while (IS_WS(str[i]))
		i++;
	if (str[i] && str[i] != COMMENT_CHAR)
		return (1);
	else if (str[i] == COMMENT_CHAR)
	{
		param->value = ft_atoi(str);
		return (2);
	}
	param->value = ft_atoi(str);
	return (0);
}

int			fill_param(char *str, t_param *param,
			t_tokens *data, uint32_t offset)
{
	int		ret;

	while (IS_WS(*str))
		str++;
	param->type = 0;
	param->value = 0;
	MCK(str = set_param_type(param, str), 1);
	if (*str == LABEL_CHAR)
		ret = search_label(data, param, str + 1, offset);
	else
		ret = get_param_value(str, param);
	return (ret);
}

t_instr		*parse_params(char *line, t_tokens *data,
			t_instr *instr, uint32_t offset)
{
	extern t_op op_tab[];
	int			i;
	int			ret;
	char		**params;
	char		*comment;

	if ((comment = ft_strchr(line, COMMENT_CHAR)))
		*comment = '\0';
	params = ft_strsplit(line, SEPARATOR_CHAR);
	i = 0;
	while (params[i])
	{
		ret = fill_param(params[i], instr->param + i, data, offset);
		i++;
		if (ret == 2)
			break ;
		else if (ret == 1)
		{
			syntax_error("invalid parameter");
			return (NULL);
		}
	}
	instr->num_params = i;
	ft_strvdel(params);
	return (instr);
}
