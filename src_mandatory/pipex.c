/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:31:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/10 17:43:05 by rimarque         ###   ########.fr       */
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
				ft_printf("pipex: no such file or directory: %s\n", str);
			else
			{
				dup2(stdout_copy, STDOUT_FILENO);
				if (ft_strncmp("/bin/", str, 5) && ft_strncmp("bin/", str, 4) && ft_strncmp("./", str, 2))
					ft_printf("pipex: command not found: %s\n", str);
				else
					ft_printf("pipex: no such file or directory: %s\n", str);
			}
			//ft_printf("flag: %d\n", flag);
			if (flag == 1)
				ft_free_str(&pathname);
			ft_free_array(&command);
			exit(exit_code);
	}
}

char	*create_pathname(char *str, int *flag)
{
	if (!ft_strncmp("./", str, 2))
		str = str + 2;
	else if (ft_strncmp("/bin/", str, 5) && (ft_strncmp("bin/", str, 4)))
	{
		*flag = 1;
		str = ft_strjoin("/bin/", str);
	}
	return (str);
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
	char	*str;
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
		str = command[0];
		pathname = create_pathname(command[0], &flag);
		if (!strncmp("./", command[0], 2))
		{
			command[0] = command[0] + 2;
			error = execve((const char *)pathname, (char **const)command, envp);
			command[0] = command[0] - 2;
		}
		else
			error = execve((const char *)pathname, (char **const)command, envp);
		error_management(error, str, 127, stdout_copy, command, pathname, flag);
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
		pathname = create_pathname(command[0], &flag);
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
