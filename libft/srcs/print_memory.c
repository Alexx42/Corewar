/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 10:28:16 by exam              #+#    #+#             */
/*   Updated: 2018/10/02 10:28:21 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include "ft_printf.h"

void	put_hex(unsigned char byte)
{
	char	hex[] = "0123456789abcdef";

	ft_putchar(hex[(byte & 0xF0) / 16]);
	ft_putchar(hex[byte & 0x0F]);
}

void	put_rep(unsigned char *read, size_t size, size_t i)
{
	size_t	j;

	j = 0;
	while (i < size && j < 16)
	{
		if (read[i] >= 32 && read[i] <= 126)
			ft_putchar(read[i]);
		else
			ft_putchar(46);
		i++;
		j++;
	}
}

void	print_memory(const void *addr, size_t size)
{
	unsigned char *read;
	size_t 			i;

	read = (unsigned char*)addr;
	if (!read)
		return ;
	i = 0;
	while (i < size || i % 64 != 0)
	{
		if (i % 64 == 0)
			ft_printf("0x%.4x : ", i);
		if (i < size)
			put_hex(read[i]);
		else
			write(1, "  ", 2);
		i++;
		ft_putchar(32);
		if (i % 64 == 0)
		{
			// put_rep(read, size, i - 16);
			ft_putchar('\n');
		}
	}
}
