/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprevost <dprevost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 12:41:05 by acakste           #+#    #+#             */
/*   Updated: 2018/11/12 08:13:46 by dprevost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_opts		g_opts;

static void	init_opts(t_opts *opts)
{
	opts->vizualizer = 0;
	opts->dump_cycle = -1;
	opts->aff = 0;
}

static int	usage(int ret)
{
	ft_putstr("corewar [-a] [-v] [-dump <cycle>] ");
	ft_putstr("[[-n <player number>] <executable> ...] \n");
	return (ret);
}

static int	usage_error(char *msg, int ret)
{
	ft_putendl(msg);
	return (usage(ret));
}

static int	parse_args(char **av, t_opts *opts)
{
	int i;

	i = 0;
	init_opts(opts);
	while (av[i])
	{
		if (*av[i] != '-')
			return (i);
		if (ft_strcmp(av[i], "-dump") == 0)
		{
			if (av[i + 1] == NULL)
				return (usage(-1));
			if (!ft_isdigit(*av[i + 1]) ||
				(opts->dump_cycle = ft_atoi(av[++i])) < 0)
				return (usage_error("invalid dump cycle", -1));
		}
		else if (ft_strcmp(av[i], "-v") == 0)
			opts->vizualizer = 1;
		else if (ft_strcmp(av[i], "-a") == 0)
			opts->aff = 1;
		else
			return (usage_error("unsupported option", -1));
		i++;
	}
	return (i);
}

int			main(int ac, char **av)
{
	t_player		players[MAX_PLAYERS];
	int				i;
	int				j;
	unsigned char	*mem;

	(void)ac;
	i = 1;
	if ((j = parse_args(av + i, &g_opts)) == -1)
		return (1);
	i += j;
	if (i == ac)
		return (error("No player specified"));
	if (parse_player_args(av + i, players))
		return (1);
	init_arena(players, &mem);
	main_schedule(players, mem, g_opts);
	return (0);
}
