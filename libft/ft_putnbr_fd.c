/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 02:07:15 by cwon              #+#    #+#             */
/*   Updated: 2024/09/08 16:27:19 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	result;

	result = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		result++;
	}
	return (result);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		digits;
	char	number[10];
	int		decimal_digit;
	int		i;

	digits = count_digits(n);
	i = digits - 1;
	if (n < 0)
		write(fd, "-", 1);
	while (i >= 0)
	{
		decimal_digit = n % 10;
		if (decimal_digit < 0)
			decimal_digit *= -1;
		number[i] = decimal_digit + '0';
		n /= 10;
		i--;
	}
	write(fd, number, digits);
}
