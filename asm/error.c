/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 18:32:48 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/06 13:04:55 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		error(char *msg)
{
	ft_putendl(msg);
	return (1);
}

void	*error_null(char *msg)
{
	ft_putendl(msg);
	return (NULL);
}

void	*error_line_nb(int line_nb)
{
	ft_putstr(" line ");
	ft_putnbr(line_nb);
	ft_putchar('\n');
	return (NULL);
}

int		syntax_error(char *msg)
{
	ft_putstr("syntax error: ");
	ft_putstr(msg);
	return (1);
}

int		lexical_error(char *msg)
{
	ft_putstr("lexical error: ");
	ft_putstr(msg);
	return (1);
}
