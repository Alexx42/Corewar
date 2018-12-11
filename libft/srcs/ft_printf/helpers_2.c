/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:40:56 by acakste           #+#    #+#             */
/*   Updated: 2018/09/22 18:40:57 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*ft_strdup_wide(wchar_t *s1)
{
	char	*dup;
	int		i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	dup = (char*)malloc(sizeof(char) * i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = (char)s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_str_of_char(int c)
{
	char *new;

	if (c == '\0')
	{
		new = (char*)malloc(sizeof(char) * 1);
		new[1] = '\0';
		return (new);
	}
	new = (char*)malloc(sizeof(char) * 2);
	if (!new)
		return (NULL);
	new[0] = (char)c;
	new[1] = '\0';
	return (new);
}
