/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 07:55:19 by cwon              #+#    #+#             */
/*   Updated: 2025/07/04 08:47:38 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static bool	skip_sign_and_validate(const char **str, bool *negative)
{
	*negative = false;
	if (**str == '-')
	{
		*negative = true;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (ft_isdigit((unsigned char)**str));
}

static size_t	count_digits(const char *str)
{
	size_t	len;

	len = 0;
	while (ft_isdigit((unsigned char)str[len]))
		len++;
	return (len);
}

static bool	compare_with_limit(const char *start, const char *limit)
{
	size_t	i;

	i = 0;
	while (i < 19)
	{
		if (start[i] < limit[i])
			return (true);
		if (start[i] > limit[i])
			return (false);
		i++;
	}
	return (true);
}

bool	is_numeric_long(const char *str)
{
	bool		negative;
	const char	*long_limit;
	const char	*start;
	size_t		len;

	if (!str || *str == '\0' || !skip_sign_and_validate(&str, &negative))
		return (false);
	while (*str == '0')
		str++;
	start = str;
	len = count_digits(str);
	if (str[len])
		return (false);
	long_limit = "9223372036854775807";
	if (negative)
		long_limit = "9223372036854775808";
	if (len < 19)
		return (true);
	if (len > 19)
		return (false);
	return (compare_with_limit(start, long_limit));
}

long	str_to_long(const char *str)
{
	bool	negative;
	long	result;

	negative = false;
	result = 0;
	if (*str == '-')
	{
		negative = true;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*(str++) - '0');
	if (negative)
		return (-1 * result);
	return (result);
}
