/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_first_fork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:08:56 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/24 20:16:22 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*read_stdin(char *lim, int n)
{
	int		temp;
	char	*str;
	char	*buff;

	str = "\0";
	buff = "\0";
	temp = n;
	while(1)
	{
		n = temp;
		while(n--)
			ft_printf("pipe ");
		ft_printf("heredoc> ");
		str = get_next_line(STDIN_FILENO);
		if (!strncmp(lim, str, strlen(lim)))
		{
			ft_free_str(&str);
			break ;
		}
		buff = ft_strjoinfree(buff, str);
		ft_free_str(&str);
	}
	return (buff);
}

int	redirect(char *lim, int n)
{
	int		heredoc_fd[2];
	char	*buff;

	if (pipe(heredoc_fd) == -1)
		error_management(NULL, 0, errno);
	buff = read_stdin(lim, n);
	write(heredoc_fd[1], buff, strlen(buff));
	close(heredoc_fd[1]);
	ft_free_str(&buff);
	return(heredoc_fd[0]);
}

int	open_file(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_management(file, 0, 0);
	return(fd);
}

void	write_to_pipe(int in_fd, int *pipe_fd, char *cmd, char **envp)
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

int	first_fork(int	*pipe_fd, int argc, char	**argv, char	**envp, int *index)
{
	int		pid;
	char	*cmd;
	int		in_fd;

	if (!strcmp(argv[1], "here_doc"))
	{
		*index = 4;
		cmd = argv[3];
		in_fd = redirect(argv[2], argc - 5);
	}
	else
	{
		*index = 3;
		cmd = argv[2];
		in_fd = open_file(argv[1]);
	}
	pid = fork();
	if (pid == -1)
		error_management(NULL, 0, errno);
	if (pid == 0)
		write_to_pipe(in_fd, pipe_fd, cmd, envp);
	return(pid);
}
