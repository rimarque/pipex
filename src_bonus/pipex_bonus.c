/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:08:56 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/22 21:26:21 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_cmd(int stdout_copy, char *str_cmd, char **envp)
{
	char	*pathname;
	char	**cmd;
	int		error;
	int		flag;

	//dup2(stdout_copy, STDOUT_FILENO);
	//ft_printf("entra aqui");
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
		error_management(cmd[0], stdout_copy, 0);
	free_and_exit(127, cmd, pathname, flag);
}

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

void	read_from_file(int *pipe_fd, char *file, char *cmd, char **envp, int *fd_file)
{
	int		file_fd;
	int		stdout_copy;

	close(pipe_fd[0]);
	stdout_copy = dup(1);
	if (!file)
	{
		dup2(*fd_file, STDIN_FILENO);
		close(*fd_file);
	}
	else
	{
		file_fd = open(file, O_RDONLY);
		if (file_fd == -1)
			error_management(file, 0, 1);
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
	}
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	exec_cmd(stdout_copy, cmd, envp);
}

int	first_fork(int	*fd, char	**argv, char	**envp, int *index)
{
	int		pid;
	int		*fd_file;

	pid = fork();
	if (pid == -1)
		error_management(NULL, 0, errno);
	if (!strcmp(argv[1], "here_doc"))
	{
		*index = 4;
		if (pid == 0)
		{
			*fd_file = redirect(fd, argv[2], argv[3], envp);
			read_from_file(fd, NULL , argv[3], envp, fd_file);
			//close(*fd_file);
		}
	}
	else
	{
		*index = 3;
		if (pid == 0)
			read_from_file(fd, argv[1], argv[2], envp, 0);
	}
	return(pid);
}

int	redirect(int *fd, char *lim, char *cmd, char **envp)
{
	int		stdout_copy;
	char	*str;
	int		file_fd;

	str = "\0";
	close(fd[0]);
	file_fd = open("file", O_WRONLY | O_RDONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd == -1)
		error_management("file", 0, 1);
	stdout_copy = dup(1);
	//ft_printf("pipe heredoc> ");
	//str = get_next_line(STDIN_FILENO);
	//ft_printf("str: %s", str);
	//ft_printf("lim: %s", lim);
	//ft_printf("%d\n", (strncmp(lim, str, 3) != 0));
	while(1)
	{
		//ft_printf("entra daqui\n");
		//dup2(stdout_copy, STDOUT_FILENO);
		//close(stdout_copy);
		ft_printf("pipe heredoc> ");
		str = get_next_line(STDIN_FILENO);
		if (!strncmp(lim, str, 3))
			break ;
		//ft_printf("str: %s", str);
		write(file_fd, (const void*)str, sizeof(str));
	}
	close(file_fd);
	//ft_printf("sai daqui\n");
	return(file_fd);
}
