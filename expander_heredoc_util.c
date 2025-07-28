/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:19:20 by cwon              #+#    #+#             */
/*   Updated: 2025/07/28 14:25:06 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"
#include "expander.h"

static int	open_heredoc_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		perror("open");
	return (fd);
}

static bool	read_heredoc_line(char **line)
{
	size_t	len;

	ft_putstr_fd("> ", STDOUT_FILENO);
	if (!get_next_line(STDIN_FILENO, line))
		return (false);
	len = ft_strlen(*line);
	if (len > 0 && (*line)[len - 1] == '\n')
		(*line)[len - 1] = 0;
	return (true);
}

static bool	write_heredoc_line(int fd, const char *line)
{
	if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
	{
		perror("write");
		return (false);
	}
	return (true);
}

static void	collect_heredoc_loop(char **line, bool *result, int fd, \
const char *delim)
{
	while (true)
	{
		if (!read_heredoc_line(line))
		{
			*result = false;
			break ;
		}
		if (!ft_strcmp(*line, delim))
		{
			free(*line);
			break ;
		}
		if (!write_heredoc_line(fd, *line))
		{
			free(*line);
			*result = false;
			break ;
		}
		free(*line);
		*line = 0;
	}
}

bool	collect_heredoc(const char *delim, const char *filename)
{
	bool	result;
	char	*line;
	int		fd;

	fd = open_heredoc_file(filename);
	if (fd < 0)
		return (false);
	line = 0;
	result = true;
	collect_heredoc_loop(&line, &result, fd, delim);
	if (!result)
	{
		if (fd >= 0)
			close(fd);
		unlink(filename);
	}
	else
		close(fd);
	return (result);
}
