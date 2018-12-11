/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:19:31 by dprevost          #+#    #+#             */
/*   Updated: 2018/11/12 14:45:00 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	disp_change_dst(unsigned char *pc, int len, int player_num)
{
	int b;
	int a;
	unsigned char *mem_start;
	unsigned char *d;

	mem_start = get_mem_start();
	d = pc;
	while(len--)
	{
		find_loc(mem_start, d, &b, &a);
		attron(COLOR_PAIR(player_num));
		mvprintw(b, a, "%.2x", *d);
		d = get_pc_moved(d, 1, 0);
		attroff(COLOR_PAIR(player_num));
		refresh();
	}
	return ;
}

void	print_carry(int carry, char *str)
{
	mvprintw((MEM_SIZE * 3) / SIZE_SCREEN + 30, 0, "Carry (%s) = %d ", str, carry);
}

void	disp_aff(char aff)
{
	mvprintw((MEM_SIZE * 3) / SIZE_SCREEN + 31, 0, "AFF = %c", aff);
}

void	disp_list_pc(t_process *processes)
{
	t_process	*tmp;

	tmp = processes;
	while(tmp)
	{
		disp_pc(tmp->pc, tmp->old_pc, tmp);
		tmp = tmp->next;
	}
}

void	disp_pc(unsigned char *pc, unsigned char *old, t_process *curr)
{
	int				a;
	int				b;
	int				aold;
	int				bold;
	unsigned char	*mem_start;

	a = 1;
	b = 0;
	*curr = *curr;
	mem_start = get_mem_start();
	if (pc)
		find_loc(mem_start, pc, &b, &a);
	if (old)
	{
		find_loc(mem_start, old, &bold, &aold);
		attron(A_COLOR & mvwinch(stdscr, bold, aold));
		attroff(A_STANDOUT);
		mvprintw(bold, aold, "%.2x", *old);
		attroff(A_COLOR & mvwinch(stdscr, bold, aold));
	}
	attron(A_STANDOUT);
	attron(A_COLOR & mvwinch(stdscr, b, a));
	mvprintw(b, a, "%.2x", *pc);
	attroff(A_STANDOUT | A_COLOR);
}

void	find_loc(unsigned char *mem, unsigned char *pc, int *b, int *a)
{
	*b = (pc - mem) / SIZE_SCREEN;
	*a = (pc - mem) % SIZE_SCREEN * 3;
}
