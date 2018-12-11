/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:31:05 by acakste           #+#    #+#             */
/*   Updated: 2018/09/18 16:32:08 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <wchar.h>
# include <inttypes.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "struct.h"
# include "libft.h"
# define TRUE 1
# define FALSE 0
# define BASE_10 "0123456789"
# define BASE_16_L "0123456789abcdef"
# define BASE_16_U "0123456789ABCDEF"
# define BASE_8 "01234567"
# define BASE_2 "01"
# define INT(x) (x == 'd' || x == 'i')
# define LONG(x) (x == 'D' || x == 'I')
# define STR(x) (x == 's' || x == 'S')
# define CHR(x) (x == 'c' || x == 'C')
# define OCT(x) (x == 'o' || x == 'O')
# define FLAGS(x) (x == '0' || x == '#' || x == '-' || x == '+' || x == ' ')

int		ft_num_len(intmax_t num, int base_len);
int		ft_num_len_unsigned(uintmax_t num, int base_len);
char	*ft_itoa_base(intmax_t num, char *base);
char	*ft_itoa_base_unsigned(uintmax_t num, char *base);
char	*ft_str_of_char(int c);
char	*ft_memaddr(uintmax_t addr, char *base);
char	*get_argument(va_list ap, t_conv_flags *flags);
char	*get_argument_hh_mod(va_list ap, t_conv_flags *flags);
char	*get_argument_h_mod(va_list ap, t_conv_flags *flags);
char	*get_argument_l_mod(va_list ap, t_conv_flags *flags);
char	*get_argument_ll_mod(va_list ap, t_conv_flags *flags);
char	*get_argument_j_mod(va_list ap, t_conv_flags *flags);
char	*get_argument_t_mod(va_list ap, t_conv_flags *flags);
char	*get_argument_z_mod(va_list ap, t_conv_flags *flags);
char	*get_argument_caps(va_list ap, t_conv_flags *flags);
char	*get_argument_sharp(va_list ap, t_conv_flags *flags);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strdup_wide(wchar_t *s1);
size_t	ft_strlen_wide(wchar_t *s);
int		ft_printf(const char *format, ...);
int		ft_sprintf(const char *format, va_list ap);
char	*read_format(char *str, const char *format, va_list ap, int *count_out);
int		read_conversion_spec(char *str, const char *format, int *count_out,
								va_list ap);
int		read_modifier(const char *format, t_conv_flags *flags);
void	strcpy_wflags(char *str, int *count_out, t_conv_flags *flags,
						va_list ap);
int		ft_atoi(const char *str);
void	*ft_increase_mem(void *ptr, size_t curr_size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	cpy_endwidth(t_conv_flags *flags, char *str, size_t raw_len);
size_t	cpy_width(t_conv_flags *flags, char *str, size_t raw_len);
size_t	cpy_0x(t_conv_flags *flags, char *str, char *raw, size_t *raw_len);
size_t	cpy_raw(t_conv_flags *flags, char *str, char *raw, size_t raw_len);
size_t	cpy_precision(t_conv_flags *flags, char *str, size_t raw_len);
void	precision_handling(t_conv_flags *flags, size_t *raw_len, char *raw);
void	precision_handling2(t_conv_flags *flags, size_t *raw_len, char *raw);

#endif
