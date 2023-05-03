/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:31:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/03 20:56:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp) //command[0] = filename; command[last] = NULL;
{
	int fd[2];
	int pid1;
	int pid2;
	int	file1;
	int file2;
	char *pathname;
	char **command;

	if (argc != 5)
		return (0);
	if(pipe(fd) == -1) //ERROR
		return (1);
	pid1 = fork();
	if (pid1 == -1) //ERROR
		return (2);
	if (pid1 == 0)
	{
		close(fd[0]);
		file1 = open(argv[1], O_RDONLY);
		dup2(file1, STDIN_FILENO);
		close(file1);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		command = ft_split(argv[2], ' ');
		pathname = ft_strjoin("/bin/", command[0]); //bin ou usr/bin
		execve((const char *)pathname, (char **const)command, envp); //LIDAR COM ERROS NO COMANDO
	}
	pid2 = fork();
	if (pid2 == -1)
		return(3);
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		file2 = open(argv[4], O_WRONLY);
		dup2(file2, STDOUT_FILENO);
		close(file2);
		command = ft_split(argv[3], ' ');
		pathname = ft_strjoin("/bin/", command[0]); //bin ou usr/bin
		execve((const char *)pathname, (char **const)command, envp); //LIDAR COM ERROS NO COMANDO
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
