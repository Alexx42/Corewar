/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduling.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 07:46:56 by acakste           #+#    #+#             */
/*   Updated: 2018/11/12 14:57:26 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <ft_printf.h>

extern		t_opts g_opts;

/*
** every cycle % CYCLE_TO_DIE
** check that every player has executed live at least once.
** add together the total number of live instructs
** those are greater than NBR_LIVE decrease CYCLE_TO_DIE by CYCLE_DELTA
** else increase the checks counter.
** if checks counter is equal to MAX_CHECKS, decrease CYCLE_TO_DIE anyways
*/

static int	update_clock(t_clock *clock, t_process **process, t_player *players)
{
	clock->num_cycles++;
	if (clock->num_cycles == clock->period_start + clock->cycle_to_die)
		if (check_death(clock, process, players))
			return (1);
	return (0);
}

static int	init_clock(t_clock *clock)
{
	int	i;

	clock->num_cycles = 0;
	clock->cycle_to_die = CYCLE_TO_DIE;
	clock->checks = 0;
	clock->period_start = 0;
	clock->processes_alive = 0;
	clock->lives_curr_period = 0;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		clock->last_live[i] = 0;
		i++;
	}
	return (0);
}

int			execute_processes(t_process *curr, t_clock *clock,
								t_process **processes)
{
	int	i;

	i = 0;
	while (curr)
	{
		read_instruct(curr, &((curr)->next_instr));
		if ((curr)->timeout)
			(curr)->timeout -= 1;
		if ((curr)->timeout == 0)
		{
			exec_instruct(curr, clock, &((curr)->next_instr), processes);
			if (g_opts.vizualizer)
				disp_pc((curr)->pc, (curr)->old_pc, curr);
		}
		curr = (curr)->next;
		i++;
	}
	if (g_opts.vizualizer)
	{
		mvprintw(MEM_SIZE / SIZE_SCREEN + 1, 0, "NUMBER OF PROCESSES");
		mvprintw(MEM_SIZE / SIZE_SCREEN + 1, 20, ": %i  ", i);
	}
	return (0);
}

int			main_schedule(t_player *players,
	unsigned char *mem, t_opts opts)
{
	t_clock		clock;
	t_process	*processes;
	t_process	*curr;

	processes = NULL;
	init_process_lst(players, &processes);
	init_clock(&clock);
	while (opts.dump_cycle == -1 || clock.num_cycles
		< (uint32_t)opts.dump_cycle)
	{
		if ((curr = processes) == NULL)
			break ;
		execute_processes(curr, &clock, &processes);
		if (opts.vizualizer)
			printer_info(clock, players, processes);
		if (update_clock(&clock, &processes, players))
			break ;
	}
	if (opts.dump_cycle >= 0 && (uint32_t)opts.dump_cycle == clock.num_cycles)
		print_memory(mem, MEM_SIZE);
	else
		get_winner(&clock, players);
	free_process_lst(processes);
	return (0);
}
