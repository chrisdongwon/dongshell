/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 00:46:35 by cwon              #+#    #+#             */
/*   Updated: 2024/09/08 17:05:36 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digit_len(int n)
{
	size_t	result;

	result = 0;
	if (!n)
		return (1);
	while (n)
	{
		result++;
		n /= 10;
	}
	return (result);
}

static int	absolute_val(int n)
{
	if (n < 0)
		return (-1 * n);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = digit_len(n);
	if (n < 0)
		len++;
	result = (char *)malloc(len + 1);
	if (result)
	{
		result[len] = 0;
		if (n < 0)
			result[0] = '-';
		if (!n)
			result[0] = '0';
		i = len - 1;
		while (n)
		{
			result[i--] = absolute_val(n % 10) + '0';
			n /= 10;
		}
	}
	return (result);
}
