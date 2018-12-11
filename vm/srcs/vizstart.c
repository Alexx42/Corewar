/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizstart.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:58:30 by dprevost          #+#    #+#             */
/*   Updated: 2018/11/07 15:00:01 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		sayhello(void)
{
	int		i;
	int		y;

	getmaxyx(stdscr, i, y);
	curs_set(0);
	mvprintw(i / 2 - 10, y / 2 - 10, "Tkobb, Ale-Goff, Acakste, Dprevost");
	mvprintw(i / 2 - 9, y / 2, "COREWAR");
	refresh();
	getch();
	erase();
	return (0);
}

int		announce_players(t_player *player)
{
	int		count;
	int		i;
	int		y;

	count = 0;
	while (count < MAX_PLAYERS)
	{
		getmaxyx(stdscr, i, y);
		if (player[count].name)
			mvprintw(i / 2 - 10, y / 2 - 10, "PLAYER %d %s",
				count + 1, player[count].name);
		refresh();
		getch();
		erase();
		count++;
	}
	return (0);
}

int		disp_winner(char *str)
{
	int		i;
	int		y;

	erase();
	nodelay(stdscr, FALSE);
	getmaxyx(stdscr, i, y);
	beep();
	beep();
	mvprintw(i / 2, y / 2 - 30,
		">>>>>>>>> %s is the winner !!! <<<<<<<<<", str);
	refresh();
	getch();
	endwin();
	return (0);
}

int		print_table_empty(void)
{
	int i;
	int a;
	int b;

	a = 0;
	b = 0;
	i = 0;
	while (i < MEM_SIZE)
	{
		mvprintw(b, a, "%.2x", 0);
		if (a + 3 < SIZE_SCREEN * 3)
			a = a + 3;
		else
		{
			a = 0;
			b++;
		}
		i++;
	}
	return (0);
}
