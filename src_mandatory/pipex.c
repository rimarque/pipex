/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:31:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/11 10:54:36 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_management(int result, char *str, int exit_code, int stdout_copy, char	**command, char	*pathname, int flag) //free stuff
{
	if (result == -1)
	{
			//printf("entra aqui");
			if (!str)
				ft_printf("pipex: %s\n", strerror(errno));
			else if (stdout_copy == 0)
				ft_printf("pipex: %s: %s\n", strerror(errno), str); //PERMISSOES - VER
			else
			{
				dup2(stdout_copy, STDOUT_FILENO);
				if (ft_strncmp("/bin/", str, 5) && ft_strncmp("bin/", str, 4) && ft_strncmp("./", str, 2))
					ft_printf("pipex: command not found: %s\n", str);
				else
					ft_printf ("pipex: %s: %s\n", strerror(errno), str);
			}
			//ft_printf("flag: %d\n", flag);
			if (flag == 1)
				ft_free_str(&pathname);
			ft_free_array(&command);
			exit(exit_code);
	}
}

char	*find_pathname(char	*command, char	*str_path, int *flag)
{
	char	*str;
	char	**path;
	char	*temp;
	int		i;

	path = ft_split(str_path, ':');
	i = 0;
	/*while(path[i])
	{
		//ft_printf("path0: %s\n", path[i]);
		i++;
	}*/
	i = 0;
	while(path[i])
	{
		//ft_printf("path0: %s\n", path[i]);
		str = ft_strjoin("/", command);
		temp = ft_strjoin(path[i], str);
		ft_free_str(&str);
		//ft_printf("temp: %s\n", temp);
		if (access((const char *)temp, F_OK) == 0)
		{
			*flag = 1;
			command = temp;
			//ft_printf("command1: %s\n", command);
			//ft_free_str(&temp);
			break;
		}
		ft_free_str(&temp);
		i++;
	}
	ft_free_array(&path);
	//ft_printf("command: %s\n", command);
	return(command);
}

char	*find_path(char	*command, char	**envp, int *flag)
{
	char	*path;
	int	i;

	path = NULL;
	i = 0;
	while(envp[i])
	{
		if(!ft_strncmp("PATH", envp[i], 4))
		{
			//ft_printf("entra aqui\n");
			path = envp[i] + 5;
			//ft_printf("path: %s\n", path);
		}
		i++;
	}
	if (path)
	{
		command = find_pathname(command, path, flag);
		//ft_printf("path1: %s\n", command);
	}
	return(command);
}

char	*create_pathname(char *command, int *flag, char	**envp)
{
	if (!ft_strncmp("./", command, 2))
		command = command + 2;
	else if (ft_strncmp("/bin/", command, 5) && (ft_strncmp("bin/", command, 4)))
	{
		command = find_path(command, envp, flag);
		//ft_printf("pathname: %s\n", command);
	}
	return (command);
}

int	main(int argc, char **argv, char **envp) //command[0] = filename; command[last] = NULL;
{
	int fd[2];
	int pid1;
	int pid2;
	int	file1;
	int file2;
	char *pathname;
	char **command;
	int	wstatus;
	int flag = 0;
	char	*main_command;
	int	error;

	if (argc != 5)
	{
		ft_printf("pipex: the program must take 4 arguments, no more, no less\n");
		return (0);
	}
	error_management(pipe(fd), NULL, errno, 0, NULL, NULL, flag);
	pid1 = fork();
	error_management(pid1, NULL, errno, 0, NULL, NULL, flag);
	if (pid1 == 0)
	{
		close(fd[0]);						//close pipe reading fd
		int stdout_copy = dup(1); 			//clone stdout to a new descriptor
		file1 = open(argv[1], O_RDONLY); 	//open fd to file1
		error_management(file1, argv[1], 1, 0, NULL, NULL, flag);
		dup2(file1, STDIN_FILENO);			//change stdin to file1
		close(file1);						//close fd of file1
		dup2(fd[1], STDOUT_FILENO);			//change stdout to pipe writing fd
		close(fd[1]);						//close pipe writing fd
		command = ft_split(argv[2], ' ');	//creating array of command
		main_command = command[0];
		//dup2(stdout_copy, STDOUT_FILENO);
		pathname = create_pathname(command[0], &flag, envp);
		//ft_printf("pathname: %s\n", pathname);
		if (!strncmp("./", command[0], 2))
		{
			command[0] = command[0] + 2;
			error = execve((const char *)pathname, (char **const)command, envp);
			command[0] = command[0] - 2;
		}
		else
			error = execve((const char *)pathname, (char **const)command, envp);
		error_management(error, main_command, 127, stdout_copy, command, pathname, flag);
	}
	waitpid(pid1, NULL, 0);
	pid2 = fork();
	if (pid2 == -1)
		return(1);
	if (pid2 == 0)
	{
		close(fd[1]);
		int stdout_copy = dup(1);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		error_management(file2, argv[4], 1, 0, NULL, NULL, flag);
		dup2(file2, STDOUT_FILENO);
		close(file2);
		command = ft_split(argv[3], ' ');
		pathname = create_pathname(command[0], &flag, envp);
		if (!strncmp("./", command[0], 2))
		{
			command[0] = command[0] + 2;
			error = execve((const char *)pathname, (char **const)command, envp);
			command[0] = command[0] - 2;
		}
		else
			error = execve((const char *)pathname, (char **const)command, envp);
		error_management(error, command[0], 127, stdout_copy, command, pathname, flag);
	}
	close(fd[0]);
	close(fd[1]);
	//printf("entra aqui");
	waitpid(pid2, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}
