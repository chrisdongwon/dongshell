/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:48:37 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 17:11:05 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../libft.h"
#include "ft_printf.h"

static void	swap(char *str, size_t i, size_t j)
{
	char	temp;

	temp = str[i];
	str[i] = str[j];
	str[j] = temp;
}

char	*pad_string(size_t n, const char c)
{
	char	*str;

	str = malloc(n + 1);
	str = ft_memset(str, c, n);
	str[n] = 0;
	return (str);
}

void	pad_zero(char **str, size_t zero_len)
{
	char	*result;
	char	*zero_str;
	char	first;
	char	second;

	zero_str = pad_string(zero_len, '0');
	result = ft_strjoin(zero_str, *str);
	if (*str[0] == '-' || *str[0] == ' ' || *str[0] == '+')
		swap(result, 0, zero_len);
	first = result[zero_len];
	second = result[zero_len + 1];
	if (first == '0' && (second == 'x' || second == 'X'))
		swap(result, 1, zero_len + 1);
	free(zero_str);
	free(*str);
	*str = result;
}

void	put_space(char *pad, size_t len, int *count)
{
	if (*count != -1 && ft_putstr_fd(pad, 1) != -1)
		*count += len;
	else
		*count = -1;
}
