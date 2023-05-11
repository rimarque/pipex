/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:31:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/11 18:45:53 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_management(int result, char *str, int exit_code, int stdout_copy, char	**command, char	*pathname, int flag) //free stuff
{
	if (result == -1)
	{
			if (!str)
				ft_printf("pipex: %s\n", strerror(errno));
			else if (stdout_copy == 0)
				ft_printf("pipex: %s: %s\n", strerror(errno), str);
			else
			{
				dup2(stdout_copy, STDOUT_FILENO);
				if (ft_strncmp("/bin/", str, 5) && ft_strncmp("bin/", str, 4) && ft_strncmp("./", str, 2))
					ft_printf("pipex: Command not found: %s\n", str);
				else if (!ft_strncmp(".sh", str + ft_strlen(str) - 3, 3))
					ft_printf("pipex: Command not found: %s\n", str);
				else
					ft_printf ("pipex: %s: %s\n", strerror(errno), str);
			}
			if (flag == 1)
				ft_free_str(&pathname);
			ft_free_array(&command);
			exit(exit_code);
	}
}

char	*create_pathname(char	*str, char	*str_path, int *flag)
{
	char	*slash_cmd;
	char	**path;
	char	*temp;
	int		i;

	path = ft_split(str_path, ':');
	i = 0;
	while(path[i])
	{
		slash_cmd = ft_strjoin("/", str);
		temp = ft_strjoin(path[i], slash_cmd);
		ft_free_str(&slash_cmd);
		if (access((const char *)temp, F_OK) == 0)
		{
			*flag = 1;
			str = temp;
			break;
		}
		ft_free_str(&temp);
		i++;
	}
	ft_free_array(&path);
	return(str);
}

char	*find_path(char	*str, char	**envp, int *flag)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while(envp[i])
	{
		if(!ft_strncmp("PATH", envp[i], 4))
			path = envp[i] + 5;
		i++;
	}
	if (path)
		str = create_pathname(str, path, flag);
	return(str);
}

char	*ft_pathname(char *str, int *flag, char	**envp, int stdout_copy, char **full_cmd)
{
	if (!ft_strncmp(".sh", str + ft_strlen(str) - 3, 3))
	{
		if (!ft_strncmp("./", str, 2))
			str = str + 2;
		else
			error_management(-1, str, 127, stdout_copy, full_cmd, NULL, 0);
	}
	else if (ft_strncmp("/bin/", str, 5) && (ft_strncmp("bin/", str, 4)))
		str = find_path(str, envp, flag);
	return (str);
}
void	exec_cmd(int	stdout_copy, char	*str_cmd, char	**envp)
{
	char	*pathname;
	char	**cmd;
	int		error;
	int		flag;

	flag = 0;
	cmd = ft_split(str_cmd, ' ');
	pathname = ft_pathname(cmd[0], &flag, envp, stdout_copy, cmd);
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

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	wstatus;
	int	pid2;

	if (argc != 5)
	{
		ft_printf("pipex: the program must take 4 arguments, no more, no less\n");
		return (0);
	}
	pid2 = ft_pipex(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}
