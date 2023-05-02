/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:31:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/02 17:45:09 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp) //command[0] = filename; command[last] = NULL;
{
	char *pathname;
	char **command;
	int	file1;

	(void)argc;
	(void)envp;
	//if (argc != 5)
	//	return (0);
	//int fd[2];
	//if(pipe(fd) == -1) //ERROR
	//	return (1);
	file1 = open(argv[1], O_RDONLY);
	dup2(file1, STDIN_FILENO);
	close(file1);
	command = ft_split(argv[2], ' ');
	pathname = ft_strjoin("/bin/", command[0]); //bin ou usr/bin
	execve((const char *)pathname, (char **const)command, envp);
	ft_free(&pathname);
	ft_free_array(&command);
	return (0);
}
