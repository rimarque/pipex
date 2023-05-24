/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:31:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/24 22:05:43 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	read_from_file(int in_fd, int *pipe_fd, char *cmd, char **envp)
{
	int	stdout_copy;

	stdout_copy = dup(1);
	close(pipe_fd[0]);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	exec_cmd(stdout_copy, cmd, envp);
}

int	pipex_first_fork(int	*pipe_fd, char	**argv, char	**envp)
{
	int		pid;
	int		in_fd;

	in_fd = open(argv[1], O_RDONLY);
	if (in_fd == -1)
		error_management(argv[1], 0, 0);
	pid = fork();
	if (pid == -1)
		error_management(NULL, 0, errno);
	if (pid == 0)
		read_from_file(in_fd, pipe_fd, argv[2], envp);
	return(pid);
}

void	read_from_pipe(int *fd, char **argv, char **envp)
{
	int		file;
	int		stdout_copy;

	close(fd[1]);
	stdout_copy = dup(1);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		error_management(argv[4], 0, 1);
	dup2(file, STDOUT_FILENO);
	close(file);
	exec_cmd(stdout_copy, argv[3], envp);
}

int	ft_pipex(int	*fd, char	**argv, char	**envp)
{
	int		pid1;
	int		pid2;

	if (pipe(fd) == -1)
		error_management(NULL, 0, errno);
	pid1 = pipex_first_fork(fd, argv, envp);
	waitpid(pid1, NULL, WNOHANG);
	pid2 = fork();
	if (pid2 == -1)
		error_management(NULL, 0, errno);
	if (pid2 == 0)
		read_from_pipe(fd, argv, envp);
	return (pid2);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	wstatus;
	int	pid2;

	if (argc != 5)
	{
		ft_printf("pipex: The program must take exactly 4 arguments\n");
		return (0);
	}
	pid2 = ft_pipex(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, &wstatus, 0);
	//ft_printf("exit status: %d\n", WEXITSTATUS(wstatus));
	return (WEXITSTATUS(wstatus));
}
