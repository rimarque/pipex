/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_last_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:05:15 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/25 16:49:34 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	write_to_file(int *pipe_fd, char *cmd, char *file, char **envp)
{
	int		file_fd;
	int		stdout_copy;

	close(pipe_fd[1]);
	stdout_copy = dup(1);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
		error_management(file, 0, 1);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	exec_cmd(stdout_copy, cmd, envp);
}

int	last_fork(int	*fd, int argc, char	**argv, char	**envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_management(NULL, 0, errno);
	if (pid == 0)
		write_to_file(fd, argv[argc - 2], argv[argc -1], envp);
	return (pid);
}
