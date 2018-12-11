/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:12:48 by acakste           #+#    #+#             */
/*   Updated: 2018/09/25 19:12:49 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef unsigned char	t_bool;

typedef struct			s_conv_flags
{
	t_bool	sharp;
	t_bool	minus;
	t_bool	plus;
	t_bool	space;
	t_bool	zero;
	t_bool	width;
	size_t	width_num;
	t_bool	precision;
	size_t	prec_num;
	t_bool	modifier;
	char	*(*arg_function)();
	char	conv;
}						t_conv_flags;

#endif
