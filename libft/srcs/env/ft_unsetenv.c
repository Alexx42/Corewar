/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 23:33:15 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/28 00:01:17 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <unistd.h>

static int	get_env_index(const char *name)
{
	extern char	**environ;
	int			i;
	char		*end;

	i = 0;
	while (environ[i])
	{
		if ((end = ft_strchr(environ[i], '=')) == NULL)
			;
		else if (ft_strncmp(environ[i], name, end - environ[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int			ft_unsetenv(const char *name)
{
	extern char	**environ;
	int			i;
	int			found;

	found = 0;
	while ((i = get_env_index(name)) != -1)
	{
		found++;
		free(environ[i]);
		while (environ[i])
		{
			environ[i] = environ[i + 1];
			i++;
		}
	}
	return (found == 0);
}
