/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:58:48 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/09 21:20:00 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "libft.h"
#include "get_next_line.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (IS_WS(line[i]))
		i++;
	if (line[i] == '\0' || line[i] == COMMENT_CHAR)
		return (1);
	return (0);
}

static void	init_tokens(t_tokens *t)
{
	t->head = NULL;
	t->tail = NULL;
	t->labels.label_def = NULL;
	t->labels.label_ref = NULL;
}

static int	parse_line(char *line, t_instr **instr,
	uint32_t *offset, t_tokens *t)
{
	char	**instrs;
	int		i;

	MCK(instrs = ft_strsplit(line, ';'), 1);
	i = 0;
	while (instrs[i])
	{
		if ((translate_line(instrs[i], instr, *offset, t)))
			return (1);
		else if (*instr)
		{
			if (validate_instr(*instr))
				return (1);
			if (*instr)
				*offset += (*instr)->out_offset;
			if (t->head == NULL)
				t->head = *instr;
			instr_lst_add(&t->tail, *instr);
			*instr = NULL;
		}
		i++;
	}
	ft_strvdel(instrs);
	return (0);
}

static void	check_error(t_tokens *t, t_header **header, uint32_t offset)
{
	if (set_undef_refs(t->labels.label_ref, t->labels.label_def))
		error("label error");
	(*header)->prog_size = offset;
	if (offset == 0)
		error("no instructions");
	while (t->labels.label_def)
	{
		free(t->labels.label_def->name);
		free(t->labels.label_def);
		t->labels.label_def = t->labels.label_def->next;
	}
	while (t->labels.label_ref)
	{
		free(t->labels.label_ref->name);
		free(t->labels.label_ref);
		t->labels.label_ref = t->labels.label_ref->next;
	}
}

t_instr		*asm_parser(t_header **header, int fd)
{
	t_tokens	t;
	t_instr		*instr;
	char		*line;
	int			line_nb;
	uint32_t	offset;

	offset = 0;
	instr = NULL;
	init_tokens(&t);
	line_nb = 0;
	MCK(*header = parse_header(fd, &line_nb), NULL);
	while (get_next_line(fd, &line) && line_nb++ >= 0)
	{
		if (is_empty_line(line))
		{
			ft_strdel(&line);
			continue ;
		}
		if (parse_line(line, &instr, &offset, &t))
			return (error_line_nb(line_nb));
		ft_strdel(&line);
	}
	check_error(&t, header, offset);
	return (t.head);
}
