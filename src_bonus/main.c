/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:47:20 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/23 19:59:41 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipe_read_and_write(int *fd, int *next_fd, char *cmd, char **envp) // ler do fd[0], escrever no next_fd[1]
{
	int	stdout_copy;

	close(fd[1]);
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
	//int i;

	//argc = 7;
	//i = index = 4;
	//argc - 3 = 4;
	ft_printf("entra aqui mltp\n");
	//i = index;
	while(index <= argc - 3) //penultimo cmd
	{
		ft_printf("entra aqui loop\n");
		close(fd[1]);
		if (pipe(next_fd) == -1)
			error_management(NULL, 0, errno);
		ft_printf("index: %d, cmd: %s\n", index, argv[index]);
		pid = fork(); //read from pipe and write on next pipe;
		if (pid == -1)
			error_management(NULL, 0, errno);
		if (pid == 0)
			pipe_read_and_write(fd, next_fd, argv[index], envp);
		waitpid(pid, NULL, 0);
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
	//int		*last_fd;
	int		fd[2];
	int		index;

	if (pipe(fd) == -1)
		error_management(NULL, 0, errno);
	pid_first = first_fork(fd, argv, envp, &index); //write to pipe 1; exec first cmd - escreves para o 1o pipe o output do 1o cmd
	waitpid(pid_first, NULL, 0);
	if (argc - (index + 1) == 1) // n == numero de pipes
	{
		ft_printf("entra aqui 4\n");
		pid_last = last_fork(fd, argc, argv, envp); //read from last pipe; exec last cmd - escreves para o ficheiro o output do ultimo comando
	}
	else
	{
		ft_printf("entra aqui else\n");
		pid_last = mltp_pipes(fd, argc, argv, envp, index);
	}
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

