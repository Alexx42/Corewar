/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 15:30:05 by acakste           #+#    #+#             */
/*   Updated: 2018/09/19 15:30:07 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

t_conv_flags	*init_flag(void)
{
	t_conv_flags *flags;

	flags = (t_conv_flags*)malloc(sizeof(t_conv_flags));
	if (!flags)
		return (NULL);
	flags->sharp = FALSE;
	flags->minus = FALSE;
	flags->plus = FALSE;
	flags->space = FALSE;
	flags->zero = FALSE;
	flags->width = FALSE;
	flags->width_num = 0;
	flags->precision = FALSE;
	flags->prec_num = 0;
	flags->modifier = FALSE;
	flags->arg_function = &get_argument;
	flags->conv = 0;
	return (flags);
}

int				read_flags(const char *format, t_conv_flags *flags)
{
	int i;

	i = 0;
	while (FLAGS(format[i]))
	{
		if (format[i] == '0')
			flags->zero = TRUE;
		else if (format[i] == '#')
			flags->sharp = TRUE;
		else if (format[i] == '-')
			flags->minus = TRUE;
		else if (format[i] == '+')
			flags->plus = TRUE;
		else if (format[i] == ' ')
			flags->space = TRUE;
		if (flags->minus == TRUE)
			flags->zero = FALSE;
		i++;
	}
	return (i);
}

int				read_width_precision(const char *format, t_conv_flags *flags)
{
	int i;

	i = 0;
	if (ft_atoi(&format[i]) != 0)
	{
		flags->width = TRUE;
		flags->width_num = ft_atoi(&format[i]);
		while (format[i] && format[i] >= '0' && format[i] <= '9')
			i++;
	}
	if (format[i] == '.')
	{
		i++;
		flags->precision = TRUE;
		flags->prec_num = ft_atoi(&format[i]);
		while (format[i] >= '0' && format[i] <= '9')
			i++;
	}
	return (i);
}

int				read_conv_char(const char *format, t_conv_flags *flags)
{
	int i;

	i = 0;
	if ((format[i] == 's' || format[i] == 'c' || format[i] == 'd' ||
		format[i] == 'i' || format[i] == 'p' || format[i] == 'o' ||
		format[i] == 'u' || format[i] == 'x') || format[i] == 'b' ||
		format[i] == 'n')
	{
		flags->conv = format[i];
		i++;
	}
	else if (format[i] == 'S' || format[i] == 'C' || format[i] == 'D' ||
			format[i] == 'I' || format[i] == 'O' || format[i] == 'U' ||
			format[i] == 'X' || format[i] == '%')
	{
		flags->conv = format[i];
		if (!flags->modifier || (flags->arg_function == get_argument_h_mod
								&& format[i] == 'U'))
			flags->arg_function = &get_argument_caps;
		i++;
	}
	return (i);
}

int				read_conversion_spec(char *str, const char *format,
							int *count_out, va_list ap)
{
	t_conv_flags	*flags;
	int				i;
	int				*n_out;

	i = 0;
	flags = init_flag();
	i += read_flags(&format[i], flags);
	i += read_width_precision(&format[i], flags);
	i += read_modifier(&format[i], flags);
	i += read_conv_char(&format[i], flags);
	if (flags->conv == 'n')
	{
		n_out = (int*)get_argument(ap, flags);
		if (n_out)
			*n_out = *count_out;
	}
	else
		strcpy_wflags(str, count_out, flags, ap);
	free(flags);
	return (i + 1);
}
