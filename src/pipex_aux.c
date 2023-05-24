/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:18:27 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/12 11:18:27 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_and_exit(int exit_code, char	**command, char	*pathname, int flag)
{
	if (flag == 1)
		ft_free_str(&pathname);
	ft_free_array(&command);
	exit(exit_code);
}

void	error_management(char *str, int stdout_copy, int exit_code)
{
	if (!str)
	{
		ft_printf("pipex: %s: %s\n", strerror(errno));
		exit(exit_code);
	}
	if (stdout_copy == 0)
	{
		ft_printf("pipex: %s: %s\n", strerror(errno), str);
		exit(exit_code);
	}
	dup2(stdout_copy, STDOUT_FILENO);
	if (ft_strncmp("/", str, 1))
		ft_printf("pipex: Command not found: %s\n", str);
	else if (!ft_strncmp(".sh", str + ft_strlen(str) - 3, 3))
		ft_printf("pipex: Command not found: %s\n", str);
	else
		ft_printf ("pipex: %s: %s\n", strerror(errno), str);
}

char	*create_pathname(char	*str, char	*str_path, int *flag)
{
	char	*slash_cmd;
	char	**path;
	char	*temp;
	int		i;

	path = ft_split(str_path, ':');
	i = 0;
	while (path[i])
	{
		slash_cmd = ft_strjoin("/", str);
		temp = ft_strjoin(path[i], slash_cmd);
		ft_free_str(&slash_cmd);
		if (access((const char *)temp, F_OK) == 0)
		{
			*flag = 1;
			str = temp;
			break ;
		}
		ft_free_str(&temp);
		i++;
	}
	ft_free_array(&path);
	return (str);
}

char	*find_path(char	*str, char	**envp, int *flag)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			path = envp[i] + 5;
		i++;
	}
	if (path)
		str = create_pathname(str, path, flag);
	return (str);
}

char	*ft_pathname(int *flag, char **envp, int stdout_copy, char **cmd)
{
	int		len;
	char	*str;

	str = "\0";
	len = ft_strlen(cmd[0]);
	if (len > 3)
	{
		if (!ft_strncmp(".sh", cmd[0] + ft_strlen(cmd[0]) - 3, 3))
		{
			if (!ft_strncmp("./", cmd[0], 2))
			{
				str = cmd[0] + 2;
				return (str);
			}
			error_management(cmd[0], stdout_copy, 0);
			free_and_exit(127, cmd, NULL, 0);
		}
	}
	if (access((const char *)cmd[0], F_OK))
		str = find_path(cmd[0], envp, flag);
	else
		str = cmd[0];
	return (str);
}
