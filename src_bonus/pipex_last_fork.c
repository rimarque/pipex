/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_last_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:05:15 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/28 14:30:16 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	write_to_file(int *pipe_fd, int argc, char **argv, char **envp)
{
	int		file_fd;
	int		stdout_copy;

	close(pipe_fd[1]);
	stdout_copy = dup(1);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	if (!strcmp(argv[1], "here_doc"))
		file_fd = open(argv[argc -1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		file_fd = open(argv[argc -1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
		error_management(argv[argc -1], 0, 1);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	exec_cmd(stdout_copy, argv[argc -2], envp);
}

int	last_fork(int	*fd, int argc, char	**argv, char	**envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_management(NULL, 0, errno);
	if (pid == 0)
		write_to_file(fd, argc, argv, envp);
	return (pid);
}
