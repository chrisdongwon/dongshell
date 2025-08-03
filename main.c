/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:53:47 by cwon              #+#    #+#             */
/*   Updated: 2025/08/01 09:02:02 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Prints usage information to standard error.
 *
 * This is an internal helper function that informs the user of the correct
 * usage of the program when the number of arguments passed is invalid.
 *
 * @param argv The argument vector passed to `main()`. 
 *             `argv[0]` should contain the program name.
 * @return Always returns EXIT_FAILURE.
 *
 * @note This function is intended for internal use only and is declared
 *       `static`.
 */
static	int	invalid_argc(char **argv)
{
	ft_putstr_fd("usage: ", STDERR_FILENO);
	ft_putstr_fd(argv[0], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

/**
 * @brief Entry point for the program.
 *
 * This function checks the number of command-line arguments and runs the
 * `minishell()` function if the argument count is correct. If the number of
 * arguments is incorrect, it prints usage information and exits with failure.
 *
 * @param argc Argument count.
 * @param argv Argument vector. `argv[0]` contains the program name.
 * @param envp Environment variables passed to the program.
 * @return EXIT_SUCCESS on success, or EXIT_FAILURE if argument count is
 *         invalid.
 */
int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (invalid_argc(argv));
	minishell(envp);
	return (EXIT_SUCCESS);
}
