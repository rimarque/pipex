/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:39:42 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/10 21:35:57 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_stringcount(char const *s, char c)
{
	size_t	count;

	count = 1;
	while (*s)
	{
		if (ft_strchr(s, c))
		{
			count++;
			s = ft_strchr(s, c);
		}
		s++;
	}
	//printf("count: %zu\n", count);
	return (count);
}

size_t	ft_stringlen(char const *s, char c)
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

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	len;
	size_t	x;

	if (!s)
		return (0);
	split = ft_calloc((ft_stringcount(s, c) + 1), sizeof(char *));
	if (!split)
		return (0);
	x = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		len = ft_stringlen(s, c);
		if (len != 0)
		{
			//printf("len: %zu\n", len);
			split[x] = ft_calloc((len + 1), sizeof(char));
			ft_strlcpy(split[x], ((char *)s), (len + 1));
			s = s + len;
			x++;
		}
	}
	//split[x] = NULL;
	return (split);
}

/*int	main()
{
	char	**split;
	char	c;
	size_t	i;

	c = ' ';
	split = ft_split("split this for me !", c);

	i = 0;
	while (split[i] != 0)
	{
		printf("%s\n", split[i]);
		i++;
	}
	ft_free_array(&split);
	return (0);
}*/
