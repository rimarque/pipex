/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:31:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/16 20:04:01 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_cmd(int stdout_copy, char *str_cmd, char **envp)
{
	char	*pathname;
	char	**cmd;
	int		error;
	int		flag;

	flag = 0;
	cmd = ft_quotes(str_cmd, ' ');
	pathname = ft_pathname(&flag, envp, stdout_copy, cmd);
	if (!strncmp("./", cmd[0], 2))
	{
		cmd[0] = cmd[0] + 2;
		error = execve((const char *)pathname, (char **const)cmd, envp);
		cmd[0] = cmd[0] - 2;
	}
	else
		error = execve((const char *)pathname, (char **const)cmd, envp);
	if (error == -1)
	{
		error_management(cmd[0], stdout_copy, 0);
		free_and_exit(127, cmd, pathname, flag);
	}
}

void	write_to_pipe(int *fd, char **argv, char **envp)
{
	int		file;
	int		stdout_copy;

	close(fd[0]);
	stdout_copy = dup(1);
	file = open(argv[1], O_RDONLY);
	if (file == -1)
		error_management(argv[1], 0, 1);
	dup2(file, STDIN_FILENO);
	close(file);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(stdout_copy, argv[2], envp);
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
	pid1 = fork();
	if (pid1 == -1)
		error_management(NULL, 0, errno);
	if (pid1 == 0)
		write_to_pipe(fd, argv, envp);
	waitpid(pid1, NULL, 0);
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
	return (WEXITSTATUS(wstatus));
}
