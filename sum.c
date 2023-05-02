#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main()
{
	int start;
	int end;
	int i;
	int sum = 0;
	int	arr[] = {1, 5, 6, 10, 2, 3, 8, 1};
	int size = sizeof(arr)/sizeof(int);
	int fd[2];
	int sumread;
	if (pipe(fd) == -1)
	{
		printf("Error creating pipe\n");
		return (1);
	}
	int id = fork();
	if (id == -1)
	{
		printf("Fork as failed\n");
		return 2;
	}
	if (id == 0)
	{
		start = 0;
		end = size/2;
	}
	else
	{
		start = size/2;
		end = size;
	}
	i = start;
	while (i < end)
	{
		sum += arr[i++];
		//printf("arr[i]:%d\n", arr[i]);
		//i++;
	}
	printf("Calculated partial sum: %d\n", sum);
	if (id == 0)
	{
		close(fd[0]);
		if(write(fd[1], &sum, sizeof(int)) == -1)
		{
			printf("Error writing to fd[1]\n");
			return 3;
		}
		close(fd[1]);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		read(fd[0], &sumread, sizeof(int));
		close(fd[0]);
		sum += sumread;
		printf("Total sum: %d\n", sum);
		//wait(NULL);
	}
	return(0);
}
