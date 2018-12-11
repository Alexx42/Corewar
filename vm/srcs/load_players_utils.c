/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_players_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:03:08 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/06 14:06:48 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int	check_magic(int fd)
{
	unsigned char	buf[4];
	uint32_t		i;

	if (read(fd, buf, 4) != 4)
		return (error("cannot read magic"));
	change_endianness((unsigned char*)buf, 4);
	ft_memcpy((void*)&i, (void*)buf, 4);
	if (i != COREWAR_EXEC_MAGIC)
		return (error("invalid magic"));
	return (0);
}

int	read_name(int fd, t_player *player)
{
	char	buf[PROG_NAME_LENGTH + 1];

	ft_bzero((void*)buf, PROG_NAME_LENGTH + 1);
	if (read(fd, buf, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		return (error("cannot read name"));
	if (lseek(fd, 4, SEEK_CUR) == -1)
		return (error("cannot seek after name"));
	MCK(player->name = ft_strdup(buf), 1);
	return (0);
}

int	read_prog_len(int fd, t_player *player)
{
	unsigned char	buf[4];
	uint32_t		len;

	if (read(fd, buf, 4) != 4)
		return (error("cannot read program length"));
	change_endianness((unsigned char*)buf, 4);
	ft_memcpy((void*)&len, buf, 4);
	player->prog_len = len;
	return (0);
}

int	read_comment(int fd, t_player *player)
{
	char	buf[COMMENT_LENGTH + 1];

	ft_bzero((void*)buf, COMMENT_LENGTH + 1);
	if (read(fd, buf, COMMENT_LENGTH) != COMMENT_LENGTH)
		return (error("comment"));
	if (lseek(fd, 4, SEEK_CUR) == -1)
		return (error("cannot seek after comment"));
	MCK(player->comment = ft_strdup(buf), 1);
	return (0);
}
