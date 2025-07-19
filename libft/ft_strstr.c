/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:11:51 by cwon              #+#    #+#             */
/*   Updated: 2025/07/18 15:42:33 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static void	compute_lps(const char *needle, size_t needle_len, int *lps)
{
	size_t	i;
	size_t	len;

	len = 0;
	lps[0] = 0;
	i = 1;
	while (i < needle_len)
	{
		if (needle[i] == needle[len])
			lps[i++] = ++len;
		else if (len)
			len = lps[len - 1];
		else
			lps[i++] = 0;
	}
}

// Knuth-Morris-Pratt algorithm
static char	*kmp_search(const char *haystack, const char *needle, \
size_t needle_len, int *lps)
{
	size_t	haystack_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	haystack_len = ft_strlen(haystack);
	while (i < haystack_len)
	{
		if (haystack[i] == needle[j])
		{
			i++;
			j++;
		}
		if (j == needle_len)
			return ((char *)(haystack + i - j));
		else if (i < haystack_len && haystack[i] != needle[j])
		{
			if (j)
				j = lps[j - 1];
			else
				i++;
		}
	}
	return (0);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		*lps;
	char	*result;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (!needle_len)
		return ((char *)haystack);
	lps = malloc(needle_len * sizeof(int));
	if (!lps)
		return (0);
	compute_lps(needle, needle_len, lps);
	result = kmp_search(haystack, needle, needle_len, lps);
	free(lps);
	return (result);
}
