/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_numeric.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:45:17 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 17:12:49 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../libft.h"
#include "ft_printf.h"

static int	pad_sign(t_spec spec, char **str)
{
	char	*result;
	char	*sign;

	if ((spec.space || spec.plus) && *str && *str[0] != '-')
	{
		sign = malloc(2);
		if (!sign)
			return (0);
		if (spec.space && spec.plus)
			spec.space = 0;
		if (spec.space)
			sign[0] = ' ';
		else if (spec.plus)
			sign[0] = '+';
		sign[1] = 0;
		result = ft_strjoin(sign, *str);
		free(sign);
		if (!result)
			return (0);
		free(*str);
		*str = result;
	}
	return (1);
}

void	convert_int(va_list *args, int *count, t_spec spec)
{
	char	*str;
	size_t	digit_len;
	size_t	len;

	str = ft_itoa(va_arg(*args, int));
	len = ft_strlen(str);
	digit_len = len;
	if (str && str[0] == '-')
		digit_len--;
	if (str && spec.dot && !spec.precision && str[0] == '0')
		empty_str(&str);
	if (spec.dot && spec.precision < 0)
		spec.dot = 0;
	if (spec.dot && spec.zero)
		spec.zero = 0;
	if (str && spec.dot && spec.precision > (int)digit_len)
		pad_zero(&str, spec.precision - digit_len);
	else if (str && spec.zero && !spec.dot && spec.width > len)
		pad_zero(&str, spec.width - len);
	if (str && pad_sign(spec, &str))
		return (format_print(spec, str, count));
	return (flush_printf(count, str));
}

void	convert_unsigned(va_list *args, int *count, t_spec spec)
{
	char	*str;
	size_t	len;

	str = ft_utoa(va_arg(*args, unsigned int));
	len = ft_strlen(str);
	if (str && spec.dot && spec.precision <= 0)
	{
		if (str[0] == '0')
			empty_str(&str);
		else
			spec.dot = 0;
	}
	if (str && spec.dot && spec.precision > (int)len)
		pad_zero(&str, spec.precision - len);
	else if (str && spec.zero && !spec.dot && spec.width > len)
		pad_zero(&str, spec.width - len);
	if (!str)
		return (flush_printf(count, str));
	return (format_print(spec, str, count));
}
