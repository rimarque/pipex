/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:56:59 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/12 11:32:04 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
#include <errno.h>
#include  "../libftx/includes/libft.h"
#include  "../libftx/includes/ft_printf.h"
#include  "../libftx/includes/get_next_line.h"

void	error_management(int result, char *str, int exit_code, int stdout_copy, char	**command, char	*pathname, int flag);
char	*create_pathname(char	*str, char	*str_path, int *flag);
char	*find_path(char	*str, char	**envp, int *flag);
char	*ft_pathname(char *str, int *flag, char	**envp, int stdout_copy, char **full_cmd);

#endif
