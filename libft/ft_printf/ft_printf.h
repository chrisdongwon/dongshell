/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:05:50 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 17:06:28 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>

typedef struct s_spec
{
	char	type;
	int		dot;
	int		minus;
	int		plus;
	int		pound;
	int		precision;
	int		space;
	int		zero;
	size_t	width;
}	t_spec;

// convert_hex.c
void	convert_hex(va_list *args, int *count, t_spec spec, const char *hex);

// convert_literal.c
void	convert_char(va_list *args, int *count, t_spec spec);
void	convert_percent_literal(int *count);
void	convert_string(va_list *args, int *count, t_spec spec);

// convert_numeric.c
void	convert_int(va_list *args, int *count, t_spec spec);
void	convert_unsigned(va_list *args, int *count, t_spec spec);

// convert_pointer.c
void	convert_pointer(va_list *args, int *count, t_spec spec);

// convert.c
void	convert(t_spec spec, va_list *args, int *count);
void	empty_str(char **str);
void	flush_printf(int *count, char *str);
void	format_print(t_spec spec, char *str, int *count);

// extract.c
void	extract(const char **str, t_spec *spec, va_list *args);

// ft_print.c
int		ft_printf(const char *format, ...);

// pad.c
char	*pad_string(size_t n, const char c);
void	pad_zero(char **str, size_t n);
void	put_space(char *pad, size_t len, int *count);

#endif
