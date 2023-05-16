/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:31:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/15 17:04:32 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_cmd(int	stdout_copy, char	*str_cmd, char	**envp)
{
	char	*pathname;
	char	**cmd;
	int		error;
	int		flag;

	flag = 0;
	//dup2(stdout_copy, STDOUT_FILENO);
	cmd = ft_quotes(str_cmd, ' ');
	//print_array(cmd);
	//ft_printf("Oi\n");
	pathname = ft_pathname(cmd[0], &flag, envp, stdout_copy, cmd);
	//ft_printf("pathname: %s\n", pathname);
	if (!strncmp("./", cmd[0], 2))
		{
			cmd[0] = cmd[0] + 2;
			error = execve((const char *)pathname, (char **const)cmd, envp);
			cmd[0] = cmd[0] - 2;
		}
	else
		error = execve((const char *)pathname, (char **const)cmd, envp);
	error_management(error, cmd[0], 127, stdout_copy, cmd, pathname, flag);
}

void	write_to_pipe(int	*fd, char	**argv, char	**envp)
{
	int		file;
	int		stdout_copy;

	close(fd[0]);
	stdout_copy = dup(1);
	file = open(argv[1], O_RDONLY);
	error_management(file, argv[1], 1, 0, NULL, NULL, 0);
	dup2(file, STDIN_FILENO);
	close(file);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(stdout_copy, argv[2], envp);
}

void	read_from_pipe(int	*fd, char	**argv, char	**envp)
{
	int		file;
	int		stdout_copy;

	close(fd[1]);
	stdout_copy = dup(1);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	error_management(file, argv[4], 1, 0, NULL, NULL, 0);
	dup2(file, STDOUT_FILENO);
	close(file);
	exec_cmd(stdout_copy, argv[3], envp);
}

int	ft_pipex(int	*fd, char	**argv, char	**envp)
{
	int		pid1;
	int		pid2;

	error_management(pipe(fd), NULL, errno, 0, NULL, NULL, 0);
	pid1 = fork();
	error_management(pid1, NULL, errno, 0, NULL, NULL, 0);
	if (pid1 == 0)
		write_to_pipe(fd, argv, envp);
	waitpid(pid1, NULL, 0);
	pid2 = fork();
	error_management(pid1, NULL, errno, 0, NULL, NULL, 0);
	if (pid2 == 0)
		read_from_pipe(fd, argv, envp);
	return(pid2);
}

int	main(int argc, char **argv, char **envp)  //VER SE FUNCIONA COM $
{
	int	fd[2];
	int	wstatus;
	int	pid2;

	if (argc != 5)
	{
		ft_printf("pipex: The program must take 4 arguments, no more, no less\n");
		return (0);
	}
	pid2 = ft_pipex(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}
