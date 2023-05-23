/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:56:59 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/23 12:21:35 by rimarque         ###   ########.fr       */
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
char	*create_pathname(char	*str, char	*str_path, int *flag);
char	*find_path(char	*str, char	**envp, int *flag);
char	*ft_pathname(int *flag, char	**envp,
			int stdout_copy, char **full_cmd);
//quotes
char	**ft_splitjoin(char *temp, char *temp2, const char *s, char c);
char	**ft_quotes(char const *s, char c);

//bonus
void	exec_cmd(int stdout_copy, char *str_cmd, char **envp);
void	write_to_file(int *pipe_fd, char *cmd, char *file, char **envp);
int		last_fork(int	*fd, int argc, char	**argv, char	**envp);
void	read_from_file(int *pipe_fd, char *file, char *cmd, char **envp);
//void	read_from_file(int *pipe_fd, char *file, char *cmd, char **envp, int *fd_file);
int		first_fork(int	*fd, char	**argv, char	**envp, int *index);
int	redirect(int *fd, char *lim, char *cmd, char **envp);

#endif
