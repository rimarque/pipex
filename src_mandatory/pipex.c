/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:31:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/05 18:13:27 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_management(int result, char *str, int exit_code, int stdout_copy)
{
	if (result == -1)
	{
			if (!str)
				ft_printf("pipex: %s\n", strerror(errno));
			else if (stdout_copy == 0)
				ft_printf("pipex: %s: %s\n", str, strerror(errno));
			else
			{
				dup2(stdout_copy, STDOUT_FILENO); //change stdout back to stdout
				if (!ft_strncmp("/bin/", str, 5) || !ft_strncmp("bin/", str, 4))
					ft_printf("pipex: %s: %s\n", str, strerror(errno));
				else
					ft_printf("pipex: %s: command not found\n", str);
			}
			ft_printf("exit code: %d\n", exit_code);
			exit(exit_code);
	}
}

/*void	error_management_commands(int result, char *str, int exit_code, int stdout_copy)
{
	if (error == -1)
	{
		dup2(stdout_copy, STDOUT_FILENO); //change stdout back to stdout
		if (!ft_strncmp("/bin/", command[0], 5) || !ft_strncmp("bin/", command[0], 4))
			ft_printf("pipex: %s: %s\n", command[0], strerror(errno));
		else
			ft_printf("pipex: %s: command not found\n", command[0]);
		exit(exit_code); //127
		}
}*/

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

	if (argc != 5)
	{
		ft_printf("pipex: the program must take 4 arguments, no more, no less\n");
		return (0);
	}
	error_management(pipe(fd), NULL, errno, 0);
	//if(pipe(fd) == -1)
	//	return (errno);
	pid1 = fork();
	error_management(pid1, NULL, errno, 0);
	//if (pid1 == -1)
	//	return (errno);
	if (pid1 == 0)
	{
		close(fd[0]);			 //close pipe reading fd
		int stdout_copy = dup(1); //clone stdout to a new descriptor
		file1 = open(argv[1], O_RDONLY);  //open fd to file1
		error_management(file1, argv[1], 1, 0);
		dup2(file1, STDIN_FILENO);        //change stdin to file1
		close(file1);                     //close fd of file1
		dup2(fd[1], STDOUT_FILENO);       //change stdout to pipe writing fd
		close(fd[1]);					  //close pipe writing fd
		command = ft_split(argv[2], ' '); //creating array of command
		pathname = ft_strjoin("/bin/", command[0]); //creanting path name for executable of comand //APRENDER A TESTAR UM SCRIPT
		int error = execve((const char *)pathname, (char **const)command, envp); //executing comand on file1 and puting output on pipe writing fd//LIDAR COM ERROS NO COMANDO
		error_management(error, command[0], 127, stdout_copy);
	}
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
		error_management(file2, argv[4], 1, 0);
		dup2(file2, STDOUT_FILENO);
		close(file2);
		command = ft_split(argv[3], ' ');
		pathname = ft_strjoin("/bin/", command[0]);
		int error = execve((const char *)pathname, (char **const)command, envp);
		error_management(error, command[0], 127, stdout_copy);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}
