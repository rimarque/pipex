/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:49:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/16 18:03:02 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3

# endif

char	*get_next_line(int fd);
char	*gnl_strjoin(char *temp, char **to_read);
void	ft_strccpy(char *dst, char *src, char c);
size_t	gnl_strclen(const char *str, char c);
int		count_nl(char *str);

#endif
