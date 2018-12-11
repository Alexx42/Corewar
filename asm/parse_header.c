/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:28:35 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/06 19:13:27 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "libft.h"
#include "get_next_line.h"

static int		get_name_directive(t_header *header, char *name, char *value)
{
	if (ft_strcmp(name, NAME_CMD_STRING))
		return (1);
	if (value == NULL)
		return (error("empty name"));
	if (ft_strlen(value) >= PROG_NAME_LENGTH)
		return (error("invalid name length"));
	header->prog_name = value;
	return (0);
}

static int		get_comment_directive(t_header *header, char *name, char *value)
{
	if (ft_strcmp(name, COMMENT_CMD_STRING))
		return (1);
	if (value == NULL)
		return (error("empty comment"));
	if (ft_strlen(value) >= COMMENT_LENGTH)
		return (error("invalid comment length"));
	header->comment = value;
	return (0);
}

static t_header	*init_header(void)
{
	t_header	*header;

	MCK(header = (t_header*)malloc(sizeof(t_header)), NULL);
	header->magic = COREWAR_EXEC_MAGIC;
	header->comment = NULL;
	header->prog_name = NULL;
	return (header);
}

t_header		*parse_header(int fd, int *line_nb)
{
	t_header	*header;
	char		*name;
	char		*value;
	int			i;

	MCK(header = init_header(), NULL);
	i = 0;
	while (i < 2)
	{
		if (parse_directive(fd, line_nb, &name, &value))
			return (error_null("invalid directive"));
		if (get_name_directive(header, name, value) == 0)
			;
		else if (get_comment_directive(header, name, value) == 0)
			;
		else
			ft_strdel(&value);
		ft_strdel(&name);
		i++;
	}
	if (!(header->comment && header->prog_name))
		return (NULL);
	return (header);
}
