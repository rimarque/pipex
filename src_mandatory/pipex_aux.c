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

void	error_management(int result, char *str, int exit_code, int stdout_copy, char	**command, char	*pathname, int flag)
{
	if (result == -1)
	{
			if (!str)
				ft_printf("pipex: %s\n", strerror(errno));
			else if (stdout_copy == 0)
				ft_printf("pipex: %s: %s\n", strerror(errno), str);
			else
			{
				dup2(stdout_copy, STDOUT_FILENO);
				if (ft_strncmp("/bin/", str, 5) && ft_strncmp("bin/", str, 4) && ft_strncmp("./", str, 2))
					ft_printf("pipex: Command not found: %s\n", str);
				else if (!ft_strncmp(".sh", str + ft_strlen(str) - 3, 3))
					ft_printf("pipex: Command not found: %s\n", str);
				else
					ft_printf ("pipex: %s: %s\n", strerror(errno), str);
			}
			if (flag == 1)
				ft_free_str(&pathname);
			ft_free_array(&command);
			exit(exit_code);
	}
}

char	*create_pathname(char	*str, char	*str_path, int *flag)
{
	char	*slash_cmd;
	char	**path;
	char	*temp;
	int		i;

	path = ft_split(str_path, ':');
	i = 0;
	while(path[i])
	{
		slash_cmd = ft_strjoin("/", str);
		temp = ft_strjoin(path[i], slash_cmd);
		ft_free_str(&slash_cmd);
		if (access((const char *)temp, F_OK) == 0)
		{
			*flag = 1;
			str = temp;
			break;
		}
		ft_free_str(&temp);
		i++;
	}
	ft_free_array(&path);
	return(str);
}

char	*find_path(char	*str, char	**envp, int *flag)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while(envp[i])
	{
		if(!ft_strncmp("PATH", envp[i], 4))
			path = envp[i] + 5;
		i++;
	}
	if (path)
		str = create_pathname(str, path, flag);
	return(str);
}

char	*ft_pathname(char *str, int *flag, char	**envp, int stdout_copy, char **full_cmd)
{
	int	len;

	len = ft_strlen(str);
	if (len > 3)
	{
		if (!ft_strncmp(".sh", str + ft_strlen(str) - 3, 3))
		{
			//ft_printf("entra aqui");
			if (!ft_strncmp("./", str, 2))
			{
				str = str + 2;
				return (str);
			}
			error_management(-1, str, 127, stdout_copy, full_cmd, NULL, 0);
		}
	}
	if (ft_strncmp("/bin/", str, 5) && (ft_strncmp("bin/", str, 4)))
	{
		//ft_printf("entra aqui");
		str = find_path(str, envp, flag);
	}
	return (str);
}
