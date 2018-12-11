/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 20:44:30 by dprevost          #+#    #+#             */
/*   Updated: 2018/11/12 14:55:59 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	printer_info(t_clock clock, t_player *player, t_process *processes)
{
	int			b;
	int			speed;
	static int	nap = 50;

	b = MEM_SIZE / SIZE_SCREEN + 2;
	mvprintw(b++, 0, "Cycle to die : %d  ", clock.cycle_to_die);
	mvprintw(b++, 0, "Checks : %d", clock.checks);
	mvprintw(b++, 0, "Number of cycles : %d", clock.num_cycles);
	printliveplayers(clock, &b, player);
	disp_list_pc(processes);
	speed = delay();
	if ((speed == 'u' || speed == KEY_UP) && nap >= 5)
		nap = nap - 5;
	if ((speed == 'd' || speed == KEY_DOWN) && nap < 150)
		nap = nap + 5;
	if (speed == 'm')
		nap = 0;
	napms(nap);
}

void	print_checks(t_clock clock, int *b)
{
	static int c = 0;

	c = c + clock.checks;
	wmove(stdscr, *b, 0);
	printw("checks : %d", c);
	(*b)++;
}

void	printliveplayers(t_clock clock, int *b, t_player *player)
{
	int i;
	int a;
	int	h;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		h = *b + 3 + (i % 2) * 4;
		a = SIZE_SCREEN / 3 + 50 * (i / 2);
		if (player[i].name)
		{
			attron(COLOR_PAIR(i + 1));
			mvprintw(h++, a, "Player %d : %s", i + 1, player[i].name);
			mvprintw(h++, a, "Last live   --> %d", clock.last_live[i]);
			if (player[i].dead == 1)
				mvprintw(h++, a, "PLAYER IS DEAD");
			attroff(COLOR_PAIR(i + 1));
		}
		i++;
	}
}

int		delay(void)
{
	int ch;

	ch = getch();
	mvprintw(MEM_SIZE / SIZE_SCREEN + 2, 50, "       ");
	if (ch == 32)
	{
		nodelay(stdscr, TRUE);
		mvprintw(MEM_SIZE / SIZE_SCREEN + 2, 50, "PAUSED");
		refresh();
		while (1)
		{
			ch = getch();
			if (ch == 32)
				break ;
			if (ch != -1)
			{
				nodelay(stdscr, FALSE);
				break ;
			}
		}
	}
	if (ch == '\033')
		return (deal_arrows());
	refresh();
	return (ch);
}

int		deal_arrows(void)
{
	int	ch;

	nodelay(stdscr, FALSE);
	mvprintw(0, 0, "ARROW");
	ch = getch();
	ch = getch();
	refresh();
	nodelay(stdscr, TRUE);
	if (ch == 'A')
		return ('u');
	if (ch == 'B')
		return ('d');
	return (ch);
}
