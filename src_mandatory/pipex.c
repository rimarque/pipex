/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:31:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/04 18:45:39 by rimarque         ###   ########.fr       */
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
	int	wstatus;

	if (argc != 5)
	{
		ft_printf("pipex: the program must take 4 arguments, no more, no less\n");
		return (0);
	}
	if(pipe(fd) == -1) //ERROR
		return (1);
	pid1 = fork();
	if (pid1 == -1) //ERROR
		return (2);
	if (pid1 == 0)
	{
		int stdoutCopy = dup(1); //clone stdout to a new descriptor
		close(fd[0]);			 //close pipe reading fd
		/*if (access(argv[1], R_OK) == -1) ENTRAR AQUI QUANDO N DEVE
		{
			ft_printf("pipex: %s: %s\n", argv[1], strerror(errno));
			ft_printf("oi\n");
			return(0);
		}*/
		file1 = open(argv[1], O_RDONLY);  //open fd to file1
		if (file1 == -1)
		{
			//waitpid(pid2, NULL, 0);
			dup2(stdoutCopy, STDOUT_FILENO); //change stdout back to stdout
			ft_printf("pipex: %s: %s\n", argv[1], strerror(errno));
			//ft_printf("oi\n");
			//ft_printf("pipex: %s: no sush file or directory\n", argv[1]);
			exit(3);
		}
		dup2(file1, STDIN_FILENO);        //change stdin to file1
		close(file1);                     //close fd of file1
		dup2(fd[1], STDOUT_FILENO);       //change stdout to pipe writing fd
		close(fd[1]);					  //close pipe writing fd
		command = ft_split(argv[2], ' '); //creating array of command
		pathname = ft_strjoin("/bin/", command[0]); //creanting path name for executable of comand
		int error = execve((const char *)pathname, (char **const)command, envp); //executing comand on file1 and puting output on pipe writing fd//LIDAR COM ERROS NO COMANDO
		if (error == -1)
		{
			dup2(stdoutCopy, STDOUT_FILENO); //change stdout back to stdout
			ft_printf("pipex: %s: %s\n", command[0], strerror(errno));
			//ft_printf("pipex: %s: command not found\n", command[0]);
			return(3);
		}
	}
	pid2 = fork();
	if (pid2 == -1)
		return(4);
	if (pid2 == 0)
	{
		int stdoutCopy = dup(1); //clone stdout to a new descriptor
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); //se n existir, cria com permissoes 664: you can read and write; others can only read, se existir apaga;
		if (file2 == -1)
		{
			dup2(stdoutCopy, STDOUT_FILENO); //change stdout back to stdout
			ft_printf("pipex: %s: %s\n", argv[4], strerror(errno));
			//ft_printf("pipex: %s: no sush file or directory\n", argv[4]);
			exit(3);
		}
		dup2(file2, STDOUT_FILENO);
		close(file2);
		command = ft_split(argv[3], ' ');
		pathname = ft_strjoin("/bin/", command[0]); //bin ou usr/bin
		int error = execve((const char *)pathname, (char **const)command, envp); //LIDAR COM ERROS NO COMANDO
		if (error == -1)
		{
			dup2(stdoutCopy, STDOUT_FILENO); //change stdout back to stdout
			ft_printf("pipex: %s: %s\n", command[0], strerror(errno));
			//ft_printf("pipex: %s: command not found\n", command[0]);
			return(5);
		}
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &wstatus, 0); //RETORNAR O EXIT STATUS --> VER ISTO errno?
	return (WEXITSTATUS(wstatus));
}
