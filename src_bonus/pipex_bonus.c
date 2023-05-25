/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:47:20 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/25 16:49:19 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	get_index(char	*str)
{
	int	index;

	if (!strcmp(str, "here_doc"))
		index = 4;
	else
		index = 3;
	return (index);
}

void	pipe_read_and_write(int *fd, int *next_fd, char *cmd, char **envp)
{
	int	stdout_copy;

	close(next_fd[0]);
	stdout_copy = dup(1);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(next_fd[1], STDOUT_FILENO);
	close(next_fd[1]);
	exec_cmd(stdout_copy, cmd, envp);
}

void	mltp_pipes(int	*fd, int argc, char	**argv, char	**envp)
{
	int	pid;
	int	next_fd[2];
	int	index;

	index = get_index(argv[1]);
	while (index <= argc - 3)
	{
		close(fd[1]);
		if (pipe(next_fd) == -1)
			error_management(NULL, 0, errno);
		pid = fork();
		if (pid == -1)
			error_management(NULL, 0, errno);
		if (pid == 0)
			pipe_read_and_write(fd, next_fd, argv[index], envp);
		waitpid(pid, NULL, WNOHANG);
		dup2(next_fd[0], fd[0]);
		dup2(next_fd[1], fd[1]);
		close(next_fd[1]);
		close(next_fd[0]);
		index++;
	}
}

int	ft_bonus_pipex(int argc, char	**argv, char	**envp)
{
	int		pid_first;
	int		pid_last;
	int		fd[2];
	int		index;

	if (pipe(fd) == -1)
		error_management(NULL, 0, errno);
	pid_first = first_fork(fd, argc, argv, envp);
	waitpid(pid_first, NULL, WNOHANG);
	index = get_index(argv[1]);
	if (argc - (index + 1) > 1)
		mltp_pipes(fd, argc, argv, envp);
	pid_last = last_fork(fd, argc, argv, envp);
	close(fd[0]);
	close(fd[1]);
	return (pid_last);
}

int	main(int argc, char **argv, char **envp)
{
	int	wstatus;
	int	pid2;

	if (argc < 5)
	{
		ft_printf("pipex: The program must take at least 4 arguments\n");
		return (0);
	}
	pid2 = ft_bonus_pipex(argc, argv, envp);
	waitpid(pid2, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}
