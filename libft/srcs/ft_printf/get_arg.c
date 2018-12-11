/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 15:33:59 by acakste           #+#    #+#             */
/*   Updated: 2018/09/19 15:34:00 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*get_argument(va_list ap, t_conv_flags *flags)
{
	if (flags->conv == 's')
		return (ft_strdup(va_arg(ap, char*)));
	else if (flags->conv == 'c')
		return (ft_str_of_char((int)va_arg(ap, int)));
	else if (flags->conv == 'd' || flags->conv == 'i')
		return (ft_itoa_base((int)va_arg(ap, int), BASE_10));
	else if (flags->conv == 'p')
		return (ft_memaddr((unsigned long long)va_arg(ap, void*), BASE_16_L));
	else if (flags->conv == 'o')
		return (ft_itoa_base_unsigned((unsigned int)va_arg(ap, unsigned int),
			BASE_8));
	else if (flags->conv == 'u')
		return (ft_itoa_base_unsigned((unsigned int)va_arg(ap, unsigned int),
			BASE_10));
	else if (flags->conv == 'x')
		return (ft_itoa_base_unsigned((unsigned int)va_arg(ap, unsigned int),
			BASE_16_L));
	else if (flags->conv == 'b')
		return (ft_itoa_base_unsigned((unsigned int)va_arg(ap, unsigned int),
			BASE_2));
	else if (flags->conv == 'n')
		return ((void*)va_arg(ap, void*));
	else if (flags->conv == '%')
		return (ft_strdup("%"));
	return (NULL);
}

char	*get_argument_caps(va_list ap, t_conv_flags *flags)
{
	if (flags->conv == 'S')
		return (ft_strdup_wide((wchar_t*)va_arg(ap, wchar_t*)));
	else if (flags->conv == 'C')
		return (ft_str_of_char((int)va_arg(ap, int)));
	else if (flags->conv == 'D' || flags->conv == 'I')
		return (ft_itoa_base_unsigned((unsigned long)va_arg(ap, unsigned long),
			BASE_10));
	else if (flags->conv == 'O')
		return (ft_itoa_base_unsigned((unsigned long)va_arg(ap, unsigned long),
			BASE_8));
	else if (flags->conv == 'U')
		return (ft_itoa_base_unsigned((unsigned long)va_arg(ap, unsigned long),
			BASE_10));
	else if (flags->conv == 'X')
		return (ft_itoa_base_unsigned((unsigned int)va_arg(ap, unsigned int),
			BASE_16_U));
	else if (flags->conv == '%')
		return (ft_strdup("%"));
	else
		return (NULL);
}

char	*get_argument_hh_mod(va_list ap, t_conv_flags *flags)
{
	if (flags->conv == 'd' || flags->conv == 'i')
		return (ft_itoa_base((signed char)va_arg(ap, int), BASE_10));
	else if (flags->conv == 'o')
		return (ft_itoa_base_unsigned((unsigned char)va_arg(ap, int),
			BASE_8));
	else if (flags->conv == 'u')
		return (ft_itoa_base_unsigned((unsigned char)va_arg(ap, int),
			BASE_10));
	else if (flags->conv == 'x' || flags->conv == 'X')
		return (ft_itoa_base_unsigned((unsigned char)va_arg(ap, int),
			BASE_16_L));
	else if (flags->conv == '%')
		return (ft_strdup("%"));
	else
		return (NULL);
}

char	*get_argument_h_mod(va_list ap, t_conv_flags *flags)
{
	if (flags->conv == 'd' || flags->conv == 'i')
		return (ft_itoa_base((short)va_arg(ap, int), BASE_10));
	else if (flags->conv == 'o')
		return (ft_itoa_base_unsigned((unsigned short)va_arg(ap, int),
			BASE_8));
	else if (flags->conv == 'u')
		return (ft_itoa_base_unsigned((unsigned short)va_arg(ap, int),
			BASE_10));
	else if (flags->conv == 'x' || flags->conv == 'X')
		return (ft_itoa_base_unsigned((unsigned short)va_arg(ap, int),
			BASE_16_L));
	else if (flags->conv == '%')
		return (ft_strdup("%"));
	else
		return (NULL);
}

char	*get_argument_l_mod(va_list ap, t_conv_flags *flags)
{
	if (flags->conv == 's')
		return (ft_strdup_wide((wchar_t*)va_arg(ap, wchar_t*)));
	else if (flags->conv == 'c')
		return (ft_str_of_char((int)va_arg(ap, wint_t)));
	else if (flags->conv == 'd' || flags->conv == 'i')
		return (ft_itoa_base(va_arg(ap, long), BASE_10));
	else if (flags->conv == 'o')
		return (ft_itoa_base_unsigned((unsigned long)va_arg(ap, unsigned long),
			BASE_8));
	else if (flags->conv == 'u')
		return (ft_itoa_base_unsigned((unsigned long)va_arg(ap, unsigned long),
			BASE_10));
	else if (flags->conv == 'x' || flags->conv == 'X')
		return (ft_itoa_base_unsigned(va_arg(ap, unsigned long), BASE_16_L));
	else if (flags->conv == '%')
		return (ft_strdup("%"));
	else
		return (NULL);
}
