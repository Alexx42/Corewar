/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 13:37:22 by acakste           #+#    #+#             */
/*   Updated: 2018/11/12 07:18:06 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_process	*create_process(t_player player, int player_num)
{
	t_process		*process;
	unsigned char	*reg_with_num;

	if ((process = (t_process*)malloc(sizeof(t_process))) == NULL)
		return (NULL);
	ft_bzero(process, sizeof(t_process));
	process->pc = player.initial_pc;
	process->player_num = player_num;
	reg_with_num = mem_to_reg((unsigned char*)&player_num, REG_SIZE);
	ft_memcpy(process->reg[0], reg_with_num, REG_SIZE);
	process->timeout = 0;
	process->lived_curr_period = 0;
	process->next = NULL;
	process->prev = NULL;
	return (process);
}

void		free_process_lst(t_process *p)
{
	t_process	*cur;
	t_process	*tmp;

	cur = p;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

int			init_process_lst(t_player *players, t_process **processes)
{
	int				i;
	t_process		*new;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (players[i].name)
		{
			new = create_process(players[i], (i + 1) * -1);
			new->old_pc = 0;
			if (!new)
				return (1);
			new->next = *processes;
			if (*processes)
				(*processes)->prev = new;
			*processes = new;
		}
		i++;
	}
	return (0);
}

int			rm_process(t_process **process, t_process **head)
{
	t_process	*tmp;

	if (*process)
	{
		if ((*process)->next)
			(*process)->next->prev = (*process)->prev;
		if ((*process)->prev)
			(*process)->prev->next = (*process)->next;
		else
			*head = (*process)->next;
		tmp = (*process)->next;
		free(*process);
		*process = tmp;
	}
	return (0);
}

int			rm_process_with_playnum(t_process **processes, int player_num)
{
	t_process	*curr;
	t_process	*tmp;

	curr = *processes;
	while (curr)
	{
		if (curr->player_num == player_num)
		{
			if (curr->next)
				(curr)->next->prev = (curr)->prev;
			if ((curr)->prev)
				(curr)->prev->next = (curr)->next;
			else
				*processes = curr->next;
			tmp = (curr)->next;
			free(curr);
			curr = tmp;
		}
		else
			curr = curr->next;
	}
	return (0);
}
