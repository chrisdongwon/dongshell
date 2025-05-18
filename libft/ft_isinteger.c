/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinteger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:17:48 by cwon              #+#    #+#             */
/*   Updated: 2025/01/23 13:48:28 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	extract_sign(const char **str, int *is_negative)
{
	while (ft_isspace((unsigned char)**str))
		(*str)++;
	*is_negative = 0;
	if (**str == '-')
	{
		*is_negative = 1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
}

static int	check_digits(const char *str, int is_negative)
{
	const char	*compare_str;
	size_t		i;
	size_t		length;

	length = ft_strlen(str);
	if (length > 10)
		return (0);
	if (length == 10)
	{
		compare_str = "2147483647";
		if (is_negative)
			compare_str = "2147483648";
		i = 0;
		while (i < length)
		{
			if (str[i] > compare_str[i])
				return (0);
			else if (str[i] < compare_str[i])
				break ;
			i++;
		}
	}
	return (1);
}

int	ft_isinteger(const char *str)
{
	int			is_negative;
	const char	*ptr;

	if (str == 0 || !(*str))
		return (0);
	extract_sign(&str, &is_negative);
	if (!(*str))
		return (0);
	ptr = str;
	while (*ptr)
	{
		if (!ft_isdigit((unsigned char)*(ptr++)))
			return (0);
	}
	return (check_digits(str, is_negative));
}
