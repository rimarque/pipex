/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulating_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:54:58 by rimarque          #+#    #+#             */
/*   Updated: 2023/04/29 16:35:09 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
//criar funcao para erros
//https://www.youtube.com/watch?v=6xbLgZpOBi8&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=23
//https://www.youtube.com/watch?v=8Q9CPWuRC6o&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=12
int	main()
{
	int	fd[2]; //file descriptores for the pipe; fd[0] --> read; fd[1] --> write;
	if (pipe(fd) == -1) //erro
		return(1);
	int pid1 = fork();
	if(pid1 < 0) //erro
		return (2);
	if (pid1 == 0)
	{
		//child process 1 (ls)
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO); //linux automaticly closes stdout
		close(fd[1]);
		execlp("ls", "ls", "-l", NULL);
	}
	int pid2 = fork();
	if (pid2 == -1)
		return 3;
	if (pid2 == 0)
	{
		//child process 2 (wc)
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execlp("wc", "wc", "-l", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	//close(fd[0]);
	//close(fd[1]);
	return(0);
}

//problema dos loops vem do write estar aberto no main process--> IMPORTANTE FECHAR O FD[1] NO MAIN PROCESS
