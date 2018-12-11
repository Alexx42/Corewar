/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 20:23:22 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/04 21:05:00 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include <limits.h>

static int	error(char *msg)
{
	ft_putstr("error: invalid define: ");
	ft_putendl(msg);
	return (1);
}

int		main(void)
{
	if (IND_SIZE > REG_SIZE)
		return (error("IND_SIZE > REG_SIZE"));
	if (IND_SIZE > UINT64_MAX || REG_SIZE > UINT64_MAX
	|| DIR_SIZE > UINT64_MAX)
		return (error("size > UINT64_T"));
	return (0);
}
