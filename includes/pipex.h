/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:56:59 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/25 16:43:54 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include  "../libftx/includes/libft.h"
# include  "../libftx/includes/ft_printf.h"
# include  "../libftx/includes/get_next_line.h"

//pipex_aux
void	free_and_exit(int exit_code, char	**command,
			char	*pathname, int flag);
void	error_management(char *str, int stdout_copy, int exit_code);
char	*ft_pathname(int *flag, char	**envp,
			int stdout_copy, char **full_cmd);
//pipex_exec_cmd
void	exec_cmd(int stdout_copy, char *str_cmd, char **envp);

//pipex_first_fork
int		first_fork(int	*fd, int argc, char	**argv, char	**envp);

//pipex_last_fork
int		last_fork(int	*fd, int argc, char	**argv, char	**envp);

#endif
