/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:47:31 by acakste           #+#    #+#             */
/*   Updated: 2018/11/12 14:41:26 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

extern	t_opts g_opts;

/*
** allocate memeory
** load each player's prog into memory
*/

static void	announce_player(t_player *player, int num)
{
	ft_putstr("Loading player ");
	ft_putnbr(num);
	ft_putstr(": ");
	ft_putstr(player->name);
	ft_putstr(" (");
	ft_putstr(player->comment);
	ft_putstr(")\n");
}

static int	get_num_players(t_player *players)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (i < MAX_PLAYERS)
	{
		if (players[i].name != NULL)
			num++;
		i++;
	}
	return (num);
}

static void	copy_players(t_player *players, size_t spacing,
	unsigned char *mem)
{
	int				i;
	unsigned char	*cur;

	cur = mem;
	i = 0;
	if (g_opts.vizualizer == 0)
		ft_printf("Introducing contestants..\n");
	while (i < MAX_PLAYERS)
	{
		if (players[i].name != NULL)
		{
			players[i].initial_pc = cur;
			ft_memcpy(cur, players[i].prog, players[i].prog_len);
			disp_change_dst(cur, players[i].prog_len, (i + 1));
			cur += spacing;
			if (g_opts.vizualizer == 0)
				announce_player(&players[i], (i + 1));
		}
		i++;
	}
}

int			init_arena(t_player *players, unsigned char **mem)
{
	size_t	spacing;

	MCK(*mem = ft_memalloc(MEM_SIZE), error("cannot allocate memory"));
	set_arena_mem_start(*mem);
	spacing = MEM_SIZE / get_num_players(players);
	if (g_opts.vizualizer)
		init_print(players);
	copy_players(players, spacing, *mem);
	return (0);
}

int			init_print(t_player *players)
{
	initscr();
	noecho();
	start_color();
	keypad(stdscr, TRUE);
	nodelay(stdscr, FALSE);
	sayhello();
	announce_players(players);
	init_pair(0, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	print_table_empty();
	return (0);
}
