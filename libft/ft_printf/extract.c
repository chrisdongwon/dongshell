/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:53:25 by cwon              #+#    #+#             */
/*   Updated: 2024/09/22 10:02:01 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	extract_flags(const char **str, t_spec *spec)
{
	while (!ft_ismember(**str, "cspdiuxX%*.123456789"))
	{
		if (**str == '-')
			spec->minus = 1;
		else if (**str == '0')
			spec->zero = 1;
		else if (**str == '#')
			spec->pound = 1;
		else if (**str == ' ')
			spec->space = 1;
		else if (**str == '+')
			spec->plus = 1;
		(*str)++;
	}
	if (spec->minus && spec->zero)
		spec->zero = 0;
}

static void	extract_width(const char **str, t_spec *spec, va_list *args)
{
	int	width;

	if (str && *str && **str == '*')
	{
		width = va_arg(*args, int);
		if (width < 0)
		{
			spec->minus = 1;
			width *= -1;
		}
		spec->width = width;
		(*str)++;
	}
	else
	{
		while (str && *str && ft_isdigit(**str))
		{
			spec->width = (spec->width * 10) + (**str - '0');
			(*str)++;
		}
	}
}

static void	extract_precision(const char **str, t_spec *spec, va_list *args)
{
	int	precision;

	if (str && *str && **str == '.')
	{
		spec->dot = 1;
		(*str)++;
		if (**str == '*')
		{
			precision = va_arg(*args, int);
			spec->precision = precision;
			(*str)++;
		}
		else
		{
			while (str && *str && ft_isdigit(**str))
			{
				spec->precision = (spec->precision * 10) + (**str - '0');
				(*str)++;
			}
		}
	}
}

static void	extract_type(const char **str, t_spec *spec)
{
	if (ft_ismember(**str, "cspdiuxX%"))
	{
		spec->type = **str;
		(*str)++;
	}
}

void	extract(const char **str, t_spec *spec, va_list *args)
{
	extract_flags(str, spec);
	extract_width(str, spec, args);
	extract_precision(str, spec, args);
	extract_type(str, spec);
}
