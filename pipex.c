/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1723/04/24 15:35:31 by rimarque          #+#    #+#             */
/*   Updated: 1723/04/24 15:35:31 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	(void)argc;
	int fd[2];
	int id;
	char *str = calloc(17, sizeof(char));
	int fdread = open(argv[1], O_RDONLY);
	int fdwrite = open(argv[2], O_WRONLY);
	if (fdread == -1)
	{
		printf("error creating fdread");
		return (3);
	}
	if (pipe(fd) == -1)
	{
		printf("Error creating pipe");
		return(1);
	}
	id = fork();
	if (id == -1)
	{
		printf("Error forking");
		return(2);
	}
	if (id == 0)
	{
		close(fd[0]);
		close(fdwrite);
		read(fdread, str, 17);
		close(fdread);
		write(fd[1], str, 17);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		close(fdread);
		read(fd[0], str, 17);
		write(fdwrite, str, 17);
	}
	wait(NULL);
	return (0);
}
