/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 11:20:35 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/09 19:50:42 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

static int	usage(void)
{
	ft_putendl("usage: ./asm <file>");
	return (0);
}

static void	get_out_filename(char dst[PATH_MAX], char *infile_name)
{
	char	*end;
	size_t	len;

	if ((end = ft_strrchr(infile_name, '.')) == NULL || end[1] != 's')
		len = ft_strlen(infile_name);
	else
		len = end - infile_name;
	len = len > PATH_MAX - 4 ? PATH_MAX - 4 : len;
	ft_strncpy(dst, infile_name, len);
	dst[len] = '\0';
	ft_strcat(dst, ".cor");
}

int			main(int ac, char **av)
{
	int			infd;
	int			outfd;
	char		outfile_name[PATH_MAX];
	t_instr		*instructs;
	t_header	*header;

	if (ac == 1)
		return (usage());
	if ((infd = open(av[1], O_RDONLY)) == -1)
		return (error("cannot open input file"));
	if ((instructs = asm_parser(&header, infd)) == NULL)
		return (1);
	get_out_filename(outfile_name, av[1]);
	if ((outfd = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
		return (error("cannot open oufput file"));
	if ((asm_encoder(header, instructs, outfd)))
		return (1);
	close(outfd);
	return (0);
}
