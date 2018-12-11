/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 13:11:24 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/02 13:42:18 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int value_of(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 10;
	return -1;
}

int			ft_atoi_base(int base, const char *s)
{
	int	n;
	int	v;
	int	sign;

	n = 0;
	while (*s <= ' ')
		s++;
	sign = *s == '-' ? -1 : 1;
	if (*s == '-' || *s == '+')
		s++;
	while ((v = value_of(*s++)) >= 0 && v < (int)base)
		n = n * base + v;
	return (n * sign);
}
