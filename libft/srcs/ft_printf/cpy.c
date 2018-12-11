/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_short.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:11:21 by acakste           #+#    #+#             */
/*   Updated: 2018/09/25 18:09:37 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	precision_handling2(t_conv_flags *f, size_t *raw_len, char *raw)
{
	if ((f->zero == TRUE || f->prec_num > *raw_len) &&
		f->precision && f->width_num > *raw_len)
		f->zero = FALSE;
	if (f->space == TRUE && !f->plus && (f->width_num <= *raw_len
		|| f->width_num <= f->prec_num) && raw[0] != '-' &&
		(INT(f->conv) || LONG(f->conv)) && ft_atoi(raw) >= 0)
	{
		f->width_num = (*raw_len > f->prec_num) ?
								*raw_len + 1 : f->prec_num + 1;
		f->width = TRUE;
	}
	if (f->sharp && (f->conv == 'o' || f->conv == 'O'))
	{
		f->precision = TRUE;
		f->prec_num = *raw_len + 1;
	}
	if (f->sharp == TRUE && (f->conv == 'x' ||
		f->conv == 'X') && ft_atoi(raw) != 0)
		*raw_len += 2;
}

void	precision_handling(t_conv_flags *f, size_t *raw_len, char *raw)
{
	if (f->precision == TRUE && f->prec_num == 0 && ft_atoi(raw) == 0)
		*raw_len = 0;
	if (f->precision == TRUE && *raw_len == 0 &&
		(STR(f->conv) || CHR(f->conv)))
		f->prec_num = 0;
	if (raw[0] == '\0' && (f->conv == 'c' || f->conv == 'C'))
		*raw_len = 1;
	if (f->prec_num > f->width_num)
		f->width_num = f->prec_num;
	if (f->plus == TRUE && raw[0] != '-' && f->width_num > 0)
		f->width_num -= 1;
	if (f->precision && f->prec_num >= *raw_len && raw[0] == '-')
	{
		*raw_len -= 1;
		f->width_num -= 1;
	}
	precision_handling2(f, raw_len, raw);
}

size_t	cpy_precision(t_conv_flags *f, char *str, size_t raw_len)
{
	size_t	i;

	i = 0;
	if (f->precision == TRUE && f->prec_num > raw_len)
	{
		while (i < f->prec_num - raw_len)
		{
			str[i] = '0';
			i++;
		}
	}
	return (i);
}

size_t	cpy_raw(t_conv_flags *f, char *str, char *raw, size_t raw_len)
{
	size_t i;
	size_t j;

	j = 0;
	i = 0;
	if (raw[j] == '\0' && (f->conv == 'c' || f->conv == 'C'))
	{
		str[i] = raw[j];
		return (i + 1);
	}
	if (f->precision && f->prec_num == 0 && ft_atoi(raw) == 0 && f->conv != '%')
		return (i);
	if (raw[0] == '-' && (f->zero || f->prec_num > raw_len) &&
			(INT(f->conv) || LONG(f->conv)))
		j++;
	if (f->precision && OCT(f->conv) && ft_atoi(raw) == 0)
		return (i);
	while (raw[j])
	{
		if (f->conv == 's' && f->precision == TRUE && i >= f->prec_num)
			break ;
		str[i++] = raw[j++];
	}
	return (i);
}

void	strcpy_wflags(char *str, int *count_out,
						t_conv_flags *f, va_list ap)
{
	char	*raw;
	size_t	raw_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	raw = f->arg_function(ap, f);
	if (raw == NULL)
		return ;
	raw_len = ft_strlen(raw);
	precision_handling(f, &raw_len, raw);
	if (f->zero == TRUE)
		i += cpy_0x(f, &str[i + *count_out], raw, &raw_len);
	i += cpy_width(f, &str[i + *count_out], raw_len);
	if (f->zero == FALSE)
		i += cpy_0x(f, &str[i + *count_out], raw, &raw_len);
	i += cpy_precision(f, &str[i + *count_out], raw_len);
	i += cpy_raw(f, &str[i + *count_out], raw, raw_len);
	i += cpy_endwidth(f, &str[i + *count_out], raw_len);
	*count_out += i;
	free(raw);
}
