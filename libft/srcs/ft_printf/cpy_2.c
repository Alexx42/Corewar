/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:39:23 by acakste           #+#    #+#             */
/*   Updated: 2018/09/22 18:39:24 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

size_t	cpy_0x(t_conv_flags *flags, char *str, char *raw, size_t *raw_len)
{
	if (raw[0] != '0' && (flags->conv == 'x' || flags->conv == 'X')
			&& flags->sharp == TRUE)
	{
		str[0] = '0';
		str[1] = flags->conv;
		return (2);
	}
	else if (flags->plus == TRUE && (INT(flags->conv) || LONG(flags->conv))
			&& ft_atoi(raw) >= 0)
	{
		str[0] = '+';
		return (1);
	}
	else if (raw[0] == '-' && (flags->zero == TRUE || flags->prec_num >=
					*raw_len) && (INT(flags->conv) || LONG(flags->conv)))
	{
		str[0] = '-';
		return (1);
	}
	return (0);
}

size_t	cpy_width(t_conv_flags *flags, char *str, size_t raw_len)
{
	size_t	i;
	size_t	taken;

	i = 0;
	taken = (raw_len > flags->prec_num) ? raw_len : flags->prec_num;
	if (STR(flags->conv) && flags->precision && raw_len > flags->prec_num)
		taken = flags->prec_num;
	if (flags->minus == FALSE && flags->width && flags->width_num > taken)
	{
		while (i + taken < (flags->width_num))
		{
			str[i] = (flags->zero == TRUE) ? '0' : ' ';
			i++;
		}
	}
	return (i);
}

size_t	cpy_endwidth(t_conv_flags *flags, char *str, size_t raw_len)
{
	size_t	i;
	size_t	taken;

	i = 0;
	taken = (raw_len > flags->prec_num) ? raw_len : flags->prec_num;
	if ((flags->conv == 's' || flags->conv == 'S') &&
			flags->precision && raw_len > flags->prec_num)
		taken = flags->prec_num;
	if (flags->minus == TRUE)
	{
		while (i + taken < flags->width_num)
		{
			str[i] = ' ';
			i++;
		}
	}
	return (i);
}
