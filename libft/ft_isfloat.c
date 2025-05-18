/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:20:16 by cwon              #+#    #+#             */
/*   Updated: 2025/01/14 10:16:23 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	valid_decimal(const char **nptr, int *has_digits, int *has_dot)
{
	if (!(*nptr) || !(**nptr))
		return (0);
	while (ft_isspace(**nptr))
		(*nptr)++;
	if (**nptr == '+' || **nptr == '-')
		(*nptr)++;
	while (**nptr != '\0')
	{
		if (ft_isdigit(**nptr))
			*has_digits = 1;
		else if (**nptr == '.')
		{
			if (*has_dot)
				return (0);
			*has_dot = 1;
		}
		else
			break ;
		(*nptr)++;
	}
	if (!(*has_digits))
		return (0);
	return (1);
}

static int	valid_exponent(const char **nptr)
{
	if (**nptr == 'e' || **nptr == 'E')
	{
		(*nptr)++;
		if (**nptr == '+' || **nptr == '-')
			(*nptr)++;
		if (!ft_isdigit(**nptr))
			return (0);
		while (ft_isdigit(**nptr))
			(*nptr)++;
	}
	while (ft_isspace(**nptr))
		(*nptr)++;
	return (1);
}

int	ft_isfloat(const char *nptr)
{
	int	has_digits;
	int	has_dot;

	has_digits = 0;
	has_dot = 0;
	if (!valid_decimal(&nptr, &has_digits, &has_dot) || !valid_exponent(&nptr))
		return (0);
	return (!(*nptr));
}
