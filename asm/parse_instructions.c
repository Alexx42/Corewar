/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:03:31 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/09 21:20:09 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

static char		*sub_string(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[j] && IS_WS(str[j]))
		j++;
	while (str[i + j] && !IS_WS(str[i + j]))
		i++;
	if (!str[i + j])
		return (NULL);
	MCK(ret = (char *)malloc(sizeof(char) * i + 1), NULL);
	if (i > 0)
		ft_strncpy(ret, str, i);
	else
		return (NULL);
	ret[i] = '\0';
	return (ret);
}

static char		*check_comm(char *line, t_instr *instr)
{
	int			i;
	extern t_op op_tab[];
	char		*ret;
	int			j;
	int			len;

	j = 0;
	MCK(ret = sub_string(line), NULL);
	i = -1;
	while (++i < 16)
		if (ft_strcmp(ret, op_tab[i].mnemonic) == 0)
		{
			len = ft_strlen(op_tab[i].mnemonic);
			instr->op_code = op_tab[i].op_code;
			instr->num_params = op_tab[i].num_params;
			ft_strdel(&ret);
			return (line + len);
		}
	ft_strdel(&ret);
	return (NULL);
}

int				translate_line(char *line, t_instr **instr, uint32_t offset,
				t_tokens *data)
{
	extern t_op op_tab[];
	int			i;
	char		*ret;

	i = 0;
	ret = line;
	while (IS_WS(*ret))
		ret++;
	ret = check_label(ret, &data->labels.label_def, offset);
	while (IS_WS(*ret))
		ret++;
	if (ret[i] == '\0')
		return (0);
	MCK(*instr = create_instr(), 1);
	if ((ret = check_comm(ret, *instr)) == NULL)
		return (lexical_error("invalid command"));
	MCK(*instr = parse_params(ret, data, *instr, offset), 1);
	return (0);
}
