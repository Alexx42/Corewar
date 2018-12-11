/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:45:31 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/07 14:58:30 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../op.h"
#include "vm.h"
#include "libft.h"

static int	error_pnum(char *msg)
{
	ft_putstr("invalid player number: ");
	ft_putendl(msg);
	return (1);
}

static int	parse_player_requested_nb(char **av, char **exec_names)
{
	int		i;
	int		pnum;

	if (av == NULL)
		return (1);
	i = 0;
	while (av[i])
	{
		if (ft_strcmp(av[i], "-n") == 0)
		{
			if (!(av[i + 1] && av[i + 2]))
				return (error_pnum("not enough arguments"));
			if ((pnum = ft_atoi(av[++i])) > MAX_PLAYERS || pnum <= 0)
				return (error_pnum("out of range"));
			if (exec_names[pnum - 1])
				return (error_pnum("already in use"));
			exec_names[pnum - 1] = av[++i];
		}
		i++;
	}
	return (0);
}

static int	parse_player_assigned_nb(char **av, char **exec_names)
{
	int		i;
	int		assigned_num;

	assigned_num = 1;
	if (av == NULL)
		return (1);
	i = 0;
	while (av[i])
	{
		if (*av[i] == '-')
		{
			if (!(av[++i] && av[++i]))
				return (1);
			i++;
			continue;
		}
		while (exec_names[assigned_num - 1] != NULL)
			assigned_num++;
		exec_names[assigned_num++ - 1] = av[i];
		i++;
	}
	return (0);
}

int			parse_player_args(char **av, t_player *players)
{
	char	*exec_names[MAX_PLAYERS];

	ft_memset(exec_names, 0, sizeof(char*) * MAX_PLAYERS);
	if (parse_player_requested_nb(av, exec_names))
		return (1);
	if (parse_player_assigned_nb(av, exec_names))
		return (1);
	if (load_players(exec_names, players))
		return (1);
	return (0);
}
