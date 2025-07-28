/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:19:20 by cwon              #+#    #+#             */
/*   Updated: 2025/07/28 15:31:37 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "expander.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

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

static char	strip_wrapping_quotes(char *line)
{
	char	quote;
	size_t	len;

	len = ft_strlen(line);
	if (len >= 2 && (line[0] == '\'' || line[0] == '"') && \
line[len - 1] == line[0])
	{
		quote = line[0];
		ft_memmove(line, line + 1, len - 2);
		line[len - 2] = 0;
		return (quote);
	}
	return (0);
}

static bool	write_heredoc_line(t_shell *shell, int fd, char *line)
{
	char	quote;
	t_token	*token;

	quote = strip_wrapping_quotes(line);
	token = new_token(line, ft_strlen(line), TOKEN_WORD, quote);
	if (!token)
	{
		perror("new_token");
		return (false);
	}
	expand_variable(shell, token);
	if (write(fd, token->value, ft_strlen(token->value)) == -1 || \
write(fd, "\n", 1) == -1)
	{
		free_token(token);
		perror("write");
		return (false);
	}
	free_token(token);
	return (true);
}

static void	collect_heredoc_loop(t_shell *shell, bool *result, int fd, \
const char *delim)
{
	char	*line;

	line = 0;
	while (true)
	{
		if (!read_heredoc_line(&line))
		{
			*result = false;
			break ;
		}
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		if (!write_heredoc_line(shell, fd, line))
		{
			free(line);
			*result = false;
			break ;
		}
		free(line);
		line = 0;
	}
}

bool	collect_heredoc(t_shell *shell, const char *delim, const char *filename)
{
	bool	result;
	int		fd;

	fd = open_heredoc_file(filename);
	if (fd < 0)
		return (false);
	result = true;
	collect_heredoc_loop(shell, &result, fd, delim);
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
