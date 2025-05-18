/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:24:52 by cwon              #+#    #+#             */
/*   Updated: 2024/09/15 16:26:35 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digit_len(unsigned int n)
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

char	*ft_utoa(unsigned int n)
{
	char	*result;
	size_t	len;

	len = digit_len(n);
	result = (char *)malloc(len + 1);
	result[len--] = 0;
	if (!n)
		result[len] = '0';
	while (n)
	{
		result[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
