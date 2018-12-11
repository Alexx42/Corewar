/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 18:15:44 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/01 20:50:58 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

static char	*parse_directive_name(char **name)
{
	char	*start;
	char	*end;
	char	*comment;

	start = *name;
	while (IS_WS(*start))
		start++;
	if ((comment = ft_strchr(start, COMMENT_CHAR)))
		end = comment;
	else
		end = start;
	while (*end && !IS_WS(*end) && *end != '\"')
		end++;
	*name = end;
	return (ft_strndup(start, end - start));
}

static char	*parse_directive_value(char *line, int fd, int *line_nb)
{
	char	*start;
	char	*end;
	char	*nxt_line;
	char	*tmp;

	MCK(start = ft_strdup(line), NULL);
	while ((end = ft_strchr(start, '\"')) == NULL)
	{
		if (get_next_line(fd, &nxt_line) != 1)
			return (error_null("cannot read"));
		(*line_nb)++;
		tmp = start;
		start = ft_strcjoin(start, '\n', nxt_line);
		ft_strdel(&tmp);
		ft_strdel(&nxt_line);
	}
	*end = '\0';
	return (start);
}

int			parse_directive(int fd, int *line_nb, char **name, char **value)
{
	char	*line;
	char	*cur;

	if (get_next_line(fd, &line) != 1)
		return (error("cannot read"));
	(*line_nb)++;
	cur = line;
	while (IS_WS(*cur))
		cur++;
	if (*cur != '.' || *cur == COMMENT_CHAR)
	{
		ft_strdel(&line);
		return (parse_directive(fd, line_nb, name, value));
	}
	MCK(*name = parse_directive_name(&cur), 1);
	while (IS_WS(*cur))
		cur++;
	if (*cur == '\"')
		*value = parse_directive_value(cur + 1, fd, line_nb);
	else
		*value = NULL;
	if (*cur && *cur != '\"')
		error("invalid directive");
	ft_strdel(&line);
	return (0);
}
