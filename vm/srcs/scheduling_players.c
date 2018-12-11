/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduling_players.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:31:16 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/12 14:29:17 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

extern		t_opts g_opts;

int	get_winner(t_clock *clock, t_player *players)
{
	int			i;
	uint32_t	j;
	uint32_t	max_last_live;

	i = 0;
	j = 0;
	while (i < MAX_PLAYERS)
	{
		if (players[i].name && clock->last_live[i] > max_last_live)
		{
			max_last_live = clock->last_live[i];
			j = i;
		}
		i++;
	}
	if (g_opts.vizualizer == 0)
		ft_printf("Player %d, %s (%s), won!\n",
			(j + 1), players[j].name, players[j].comment);
	else
		disp_winner(players[j].name);
	return (0);
}

int	kill_processes(t_process **processes, t_clock *clock)
{
	t_process	*cur;
	int			i;

	cur = *processes;
	i = 0;
	while (cur)
	{
		if (cur->lived_curr_period == 0)
			rm_process(&cur, processes);
		else
		{
			cur->lived_curr_period = 0;
			clock->processes_alive++;
			cur = cur->next;
		}
		i++;
	}
	return (0);
}

int	check_death(t_clock *clock, t_process **processes, t_player *players)
{
	clock->period_start = clock->num_cycles;
	clock->processes_alive = 0;
	kill_processes(processes, clock);
	if (clock->lives_curr_period < NBR_LIVE)
		clock->checks++;
	if (clock->lives_curr_period >= NBR_LIVE || clock->checks >= MAX_CHECKS)
	{
		if (clock->cycle_to_die < CYCLE_DELTA)
			return (1);
		else
			clock->cycle_to_die -= CYCLE_DELTA;
		clock->checks = 0;
	}
	clock->lives_curr_period = 0;
	return (find_dead_players(processes, players));
}

int	find_dead_players(t_process **processes, t_player *players)
{
	t_process	*tmp;
	int			j;

	j = 0;
	tmp = *processes;
	while (j < MAX_PLAYERS)
	{
		players[j].dead = 1;
		j++;
	}
	while (tmp)
	{
		players[tmp->player_num + 4].dead = 0;
		tmp = tmp->next;
	}
	return (0);
}
