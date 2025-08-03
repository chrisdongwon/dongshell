/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:19:20 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 12:37:06 by cwon             ###   ########.fr       */
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

/**
 * @brief Reads a single line of heredoc input from standard input.
 *
 * Prints the heredoc prompt "> " to stdout and reads a line from stdin.
 * If the line ends with a newline character, it is removed.
 *
 * @param line Pointer to a string pointer where the read line will be stored.
 * @return true if a line was successfully read, false if EOF or error.
 */
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

/**
 * @brief Strips matching wrapping quotes from a heredoc input line.
 *
 * If the input line starts and ends with matching single or double quotes,
 * those quotes are removed from the string in-place.
 *
 * @param line The heredoc input line to process.
 * @return The quote character that was stripped ('\'' or '\"'), or 0 if none.
 */
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

/**
 * @brief Writes a processed heredoc line to the given file descriptor.
 *
 * Strips wrapping quotes from the line, expands shell variables,
 * then writes the expanded line followed by a newline to the file descriptor.
 *
 * @param shell Pointer to the shell state for variable expansion.
 * @param fd    File descriptor to write the heredoc line to.
 * @param line  The heredoc input line to write.
 * @return true on successful write, false on failure.
 */
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
	if (quote != '\'')
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

/**
 * @brief Reads a single heredoc line with EOF warning on early termination.
 * 
 * Wraps around read_heredoc_line() and checks if EOF (Ctrl-D) was received
 * (indicated by *line == NULL). If EOF is detected before the delimiter, 
 * prints a warning message to stderr and sets *result to false.
 * 
 * @param shell Pointer to the shell state (unused here but kept for 
 *              consistency).
 * @param line Pointer to a char* that will point to the allocated line read.
 *             Must be freed by the caller if non-NULL.
 * @param delim The heredoc delimiter string, used for the EOF warning message.
 * @param result Pointer to a boolean flag; set to false on error or EOF.
 * 
 * @return true if a line was successfully read (non-NULL line), 
 *         false otherwise.
 */
static bool	read_heredoc_line_with_warning(char **line, const char *delim, \
bool *result)
{
	if (!read_heredoc_line(line))
	{
		*result = false;
		return (false);
	}
	if (*line == 0)
	{
		heredoc_eof_warning(delim);
		return (false);
	}
	return (true);
}

void	collect_heredoc_loop(t_shell *shell, bool *result, int fd, \
const char *delim)
{
	char	*line;

	line = 0;
	while (true)
	{
		if (!read_heredoc_line_with_warning(&line, delim, result))
			break ;
		if (line && delim && !ft_strcmp(line, delim))
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
