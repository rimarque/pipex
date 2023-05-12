/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:39:42 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/12 18:18:33 by rimarque         ###   ########.fr       */
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

char	**ft_makesplit(char	**split, char const *s, char c)
{
	size_t x;
	size_t	len;

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
	return(split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (0);
	split = ft_calloc((ft_stringcount(s, c) + 1), sizeof(char *));
	if (!split)
		return (0);
	split = ft_makesplit(split, s, c);
	//split[x] = NULL;
	return (split);
}

void	print_array(char	**array)
{
	int i = 0;
	while (array[i] != 0)
	{
		printf("%s\n", array[i]);
		i++;
	}
	ft_free_array(&array);
}

char	**ft_quotes(char const *s, char c)
{
	char	*temp;
	char	*str_in_quotes;
	char	**split1;
	char	**split2;
	char	**result;

	temp = ft_strchr(s, 39);
	char	*temp2 = ft_strchr(temp + 1, 39);
	if (temp2)
	{
		//printf("%c\n", *(temp - 1));
		if (temp && *(temp - 1) == c && (*(temp2 + 1) == c || *(temp2 + 1) == '\0'))
		{
			str_in_quotes = ft_substr(temp, 1, ft_stringlen(temp + 1, 39));
			printf("str in quotes:%s\n", str_in_quotes);
			char	*str1 = ft_substr(s, 0, ft_stringlen(s, 39));
			split1 = ft_split(str1, c);
			//print_array(split1);
			printf("str 1:%s\n", str1);
			char	*temp2 = ft_strchr(temp + 1, 39);
			char	*str2 = ft_substr(temp2, 1, ft_stringlen(temp + 1, '\0'));
			split2 = ft_split(str2, c);
			printf("str 2:%s\n", str2);
			//print_array(split2);
		}
	}
	else
		result = ft_split(s, c);
	return(result);
}

int	main()
{
	char	**split;
	char	c;
	size_t	i;

	c = ' ';
	split = ft_quotes("awk gsja jhsdkj jh '{count++} END {print count}", c);
	//split =
	i = 0;
	while (split[i] != 0)
	{
		printf("%s\n", split[i]);
		i++;
	}
	ft_free_array(&split);
	return (0);
}
