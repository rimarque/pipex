#include "includes/pipex.h"
#include  "libftx/includes/ft_printf.h"
#include <stdio.h>

void	print_array(char	**array)
{
	int i = 0;
	while (array[i] != 0)
	{
		printf("%s\n", array[i]);
		i++;
	}
	//ft_free_array(&array);
}

char	**ft_join_to_arr(char	*s1, char	*s2)
{
	//size_t	arr1_len;
	//size_t	arr2_len;
	char	**new_arr;

	//if (!arr1 || !str || !arr2)
	//	return (0);
	//arr1_len = ft_arrlen(arr1);
	//arr2_len = ft_arrlen(arr2);
	new_arr = malloc(3 * sizeof(char *)); //numero de str dos arrays + 1 str + 1 para null
	if (!new_arr)
		return (0);
	new_arr[0] = s1;
	//printf("%s\n", new_arr[0]);
	new_arr[1] = s2;
	//printf("%s\n", new_arr[1]);
	new_arr[2] = NULL;
	//printf("%s\n", new_arr[2]);
	return (new_arr);
}

int main(int argc, char **argv, char **envp)
{
	char	**cmd;
	cmd = ft_join_to_arr(argv[1], argv[2]);
	print_array(cmd);
	execve("/bin/awk", (char **const)cmd, envp);
}
