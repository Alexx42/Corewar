/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:47:22 by acakste           #+#    #+#             */
/*   Updated: 2018/11/07 14:58:03 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include <fcntl.h>

int			read_header(int fd, t_player *player)
{
	if (check_magic(fd)
	|| read_name(fd, player)
	|| read_prog_len(fd, player)
	|| read_comment(fd, player))
		return (1);
	return (0);
}

int			read_program(int fd, t_player *player)
{
	char	*buf;

	MCK(buf = (char*)malloc(sizeof(char) * player->prog_len), 1);
	if (read(fd, buf, player->prog_len) != player->prog_len)
		return (error("cannot read program"));
	player->prog = (void*)buf;
	return (0);
}

static int	validate_exec(t_player *player, size_t len)
{
	if (player->prog_len != len)
		return (error("program length difers"));
	if (player->prog_len > CHAMP_MAX_SIZE)
		return (error("program is too big"));
	return (0);
}

int			load_exc(char *exec_name, t_player *player)
{
	int		fd;
	off_t	prog_start;
	ssize_t	len;

	if ((fd = open(exec_name, O_RDONLY)) == -1)
		return (error("cannot open executable"));
	if (read_header(fd, player))
		return (1);
	if ((prog_start = lseek(fd, 0, SEEK_CUR)) == -1)
		return (error("cannot seek"));
	if ((len = lseek(fd, 0, SEEK_END)) == -1)
		return (error("cannot seek"));
	len -= prog_start;
	if (lseek(fd, prog_start, SEEK_SET) == -1)
		return (error("cannot seek"));
	if (validate_exec(player, len))
		return (1);
	player->prog_len = len;
	if (read_program(fd, player))
		return (1);
	return (0);
}

int			load_players(char **exec_names,
	t_player *players)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (exec_names[i])
		{
			if (load_exc(exec_names[i], &players[i]))
				return (1);
		}
		else
			players[i].name = NULL;
		i++;
	}
	return (0);
}
