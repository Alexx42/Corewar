/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 17:37:47 by acakste           #+#    #+#             */
/*   Updated: 2018/09/18 17:37:48 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*read_format(char *str, const char *format, va_list ap, int *count_out)
{
	int	count_in;

	count_in = 0;
	while (format[count_in] != '\0')
	{
		if (format[count_in] == '%')
		{
			count_in += read_conversion_spec(str, &format[count_in + 1],
												count_out, ap);
		}
		else
		{
			str[(*count_out)] = format[count_in];
			*count_out += 1;
			count_in++;
		}
	}
	str[*count_out] = '\0';
	return (str);
}

int		ft_sprintf(const char *format, va_list ap)
{
	char	*output;
	int		count_out;

	count_out = 0;
	output = (char*)malloc(sizeof(char) * 12000);
	if (!output)
		return (0);
	output = read_format(output, format, ap, &count_out);
	write(1, output, count_out);
	free(output);
	return (count_out);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		printed;

	printed = 0;
	va_start(ap, format);
	printed = ft_sprintf(format, ap);
	va_end(ap);
	return (printed);
}
