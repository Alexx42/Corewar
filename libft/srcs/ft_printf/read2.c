/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 18:27:44 by acakste           #+#    #+#             */
/*   Updated: 2018/09/25 18:27:45 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static	void	modifier_support(char c, t_conv_flags *flags)
{
	if (c == 'h')
		flags->arg_function = &get_argument_h_mod;
	else if (c == 'l')
		flags->arg_function = &get_argument_l_mod;
	else if (c == 'j')
		flags->arg_function = &get_argument_j_mod;
	else if (c == 'z')
		flags->arg_function = &get_argument_z_mod;
}

int				read_modifier(const char *format, t_conv_flags *flags)
{
	int i;

	i = 0;
	if (format[i] == 'h' || format[i] == 'l' ||
		format[i] == 'j' || format[i] == 'z')
	{
		flags->modifier = TRUE;
		modifier_support(format[i], flags);
		i++;
	}
	if (format[i] == 'h' && flags->arg_function == get_argument_h_mod)
	{
		flags->arg_function = &get_argument_hh_mod;
		i++;
	}
	if (format[i] == 'l' && flags->arg_function == get_argument_l_mod)
	{
		flags->arg_function = &get_argument_ll_mod;
		i++;
	}
	return (i);
}
