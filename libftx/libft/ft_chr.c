/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:05:04 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/16 19:31:19 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_chrcount(char const *s, char c)
{
	size_t	count;
	char	*set;

	set = ft_calloc(2, sizeof(char));
	*set = c;
	s = ft_strtrim(s, (const char *)set);
	ft_free_str(&set);
	count = 0;
	while (*s)
	{
		if (ft_strchr(s, c))
		{
			count++;
			s = ft_strchr(s, c);
			while (*s == c && *s)
				s++;
		}
		else
			s++;
	}
	return (count);
}

size_t	ft_strclen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}
