/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 07:57:40 by acakste           #+#    #+#             */
/*   Updated: 2018/09/19 07:57:44 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		ft_num_len(intmax_t num, int base_len)
{
	int	bytes;

	if (num == 0)
		return (1);
	bytes = (num < 0) ? 1 : 0;
	while (num != 0)
	{
		num /= base_len;
		bytes++;
	}
	return (bytes);
}

int		ft_num_len_unsigned(uintmax_t num, int base_len)
{
	int	bytes;

	if (num == 0)
		return (1);
	bytes = 0;
	while (num != 0)
	{
		num /= base_len;
		bytes++;
	}
	return (bytes);
}

char	*ft_itoa_base(intmax_t num, char *base)
{
	char	*buff;
	int		len;
	int		base_len;
	int		stop;

	base_len = ft_strlen(base);
	len = ft_num_len(num, base_len);
	buff = (char*)malloc(sizeof(char) * len + 1);
	buff[len] = '\0';
	len--;
	if (num < 0)
		buff[0] = '-';
	stop = (num < 0) ? 1 : 0;
	while (len >= stop)
	{
		buff[len] = (num < 0) ? base[(num % base_len) * -1]
								: base[num % base_len];
		num /= base_len;
		len--;
	}
	return (buff);
}

char	*ft_itoa_base_unsigned(uintmax_t num, char *base)
{
	char	*buff;
	int		len;
	int		base_len;

	base_len = ft_strlen(base);
	len = ft_num_len_unsigned(num, base_len);
	buff = (char*)malloc(sizeof(char) * len + 1);
	buff[len] = '\0';
	len--;
	while (len >= 0)
	{
		buff[len] = base[num % base_len];
		num /= base_len;
		len--;
	}
	return (buff);
}

char	*ft_memaddr(uintmax_t addr, char *base)
{
	char	s[3];
	char	*hex;
	char	*address;

	s[0] = '0';
	s[1] = 'x';
	s[2] = '\0';
	hex = ft_itoa_base_unsigned(addr, base);
	address = ft_strjoin(s, hex);
	free(hex);
	return (address);
}
