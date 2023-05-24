/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:47:20 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/24 22:08:25 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	mltp_pipes(int	*fd, int argc, char	**argv, char	**envp, int index)
{
	int	pid;
	int	next_fd[2];

	while(index <= argc - 3)
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
	pid = last_fork(fd, argc, argv, envp);
	return(pid);
}

int	ft_bonus_pipex(int argc, char	**argv, char	**envp)
{
	int		pid_first;
	int		pid_last;
	int		fd[2];
	int		index_seccmd;

	if (pipe(fd) == -1)
		error_management(NULL, 0, errno);
	pid_first = first_fork(fd, argc, argv, envp, &index_seccmd);
	waitpid(pid_first, NULL, WNOHANG);
	if (argc - (index_seccmd + 1) == 1)
		pid_last = last_fork(fd, argc, argv, envp);
	else
		pid_last = mltp_pipes(fd, argc, argv, envp, index_seccmd);
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
	//ft_printf("%d", WEXITSTATUS(wstatus));
	return (WEXITSTATUS(wstatus));
}
