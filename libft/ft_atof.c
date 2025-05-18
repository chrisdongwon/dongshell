/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:12:57 by cwon              #+#    #+#             */
/*   Updated: 2025/01/14 09:30:03 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	init_atof(double *power, int *sign, int *exp_sign, int *exp)
{
	*power = 1.0;
	*sign = 1;
	*exp_sign = 1;
	*exp = 0;
	return (0.0);
}

static void	extract_int(const char **nptr, double *result, int *sign)
{
	while (ft_isspace(**nptr))
		(*nptr)++;
	if (**nptr == '-')
	{
		*sign = -1;
		(*nptr)++;
	}
	else if (**nptr == '+')
		(*nptr)++;
	while (ft_isdigit(**nptr))
	{
		*result = 10.0 * *result + (**nptr - '0');
		(*nptr)++;
	}
}

static void	extract_decimal(const char **nptr, double *result, double *p, int s)
{
	if (**nptr == '.')
	{
		(*nptr)++;
		while (ft_isdigit(**nptr))
		{
			*result = 10.0 * *result + (**nptr - '0');
			*p *= 10.0;
			(*nptr)++;
		}
	}
	*result = s * *result / *p;
}

static void	extract_exp(const char **nptr, double *result, int *exp, int *sign)
{
	(*nptr)++;
	if (**nptr == '-')
	{
		*sign = -1;
		(*nptr)++;
	}
	else if (**nptr == '+')
		(*nptr)++;
	while (ft_isdigit(**nptr))
	{
		*exp = 10 * *exp + (**nptr - '0');
		(*nptr)++;
	}
	if (*sign == -1)
	{
		while ((*exp)-- > 0)
			*result /= 10.0;
	}
	else
	{
		while ((*exp)-- > 0)
			*result *= 10.0;
	}
}

double	ft_atof(const char *nptr)
{
	double	result;
	double	power;
	int		sign;
	int		exp_sign;
	int		exp;

	result = init_atof(&power, &sign, &exp_sign, &exp);
	extract_int(&nptr, &result, &sign);
	extract_decimal(&nptr, &result, &power, sign);
	if (*nptr == 'e' || *nptr == 'E')
		extract_exp(&nptr, &result, &exp, &exp_sign);
	return (result);
}
