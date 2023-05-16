/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:39:42 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/15 17:04:17 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_stringcount(char const *s, char c)
{
	size_t	count;
	char *set;

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
			//printf("count: %zu\n", count);
			//printf("s: %s\n", s);
			s = ft_strchr(s, c);
			while (*s == c && *s)
				s++;
		}
		else
			s++;
	}
	//printf("count: %zu\n", count);
	return (count + 1);
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
		ft_printf("%s\n", array[i]);
		i++;
	}
	//ft_free_array(&array);
}

char	**ft_arrjoin(char	**arr1, char	*str, char	**arr2)
{
	size_t	arr1_len;
	size_t	arr2_len;
	char	**new_arr;

	if (!arr1 || !str || !arr2)
		return (0);
	arr1_len = ft_arrlen(arr1);
	arr2_len = ft_arrlen(arr2);
	new_arr = malloc((arr1_len + arr2_len + 2) * sizeof(char *)); //numero de str dos arrays + 1 str + 1 para null
	if (!new_arr)
		return (0);
	ft_arrlcpy(new_arr, arr1, (arr1_len + 1));
	new_arr[arr1_len] = str;
	ft_arrlcpy(new_arr + arr1_len + 1, arr2, (arr2_len + 1));
	return (new_arr);
}

char	**ft_quotes(char const *s, char c)
{
	char	*temp;
	char	*temp2;
	char	*str_in_quotes;
	char	**split1;
	char	**split2;
	char	**result;

	//ft_printf("entrou aqui\n");
	temp = ft_strchr(s, 39); //transformar num loop; se for par entra, se for impar nao entra;
	//ft_printf("temp:%s\n", temp);
	if (temp)
		temp2 = ft_strchr(temp + 1, 39);
	//ft_printf("temp 2:%s\n", temp2);
	//ft_printf("entrou aqui3\n");
	//ft_printf("temp2:%s\n", temp2);
	if (temp2)
	{
		//ft_printf("entrou aqui 1\n");
		//ft_printf("%coi\n", *(temp - 1));
		if (temp && *(temp - 1) == c && (*(temp2 + 1) == c || *(temp2 + 1) == '\0'))
		{
			//ft_printf("oi");
			str_in_quotes = ft_substr(temp, 1, ft_stringlen(temp + 1, 39));
			printf("str in quotes:%s\n", str_in_quotes);
			char	*str1 = ft_substr(s, 0, ft_stringlen(s, 39));
			split1 = ft_split(str1, c);
			//print_array(split1);
			//printf("str 1:%s\n", str1);
			//char	*temp2 = ft_strchr(temp + 1, 39);
			char	*str2 = ft_substr(temp2, 1, ft_stringlen(temp + 1, 39));
			split2 = ft_split(str2, c);
			//printf("str 2:%s\n", str2);
			result = ft_arrjoin(split1, str_in_quotes, split2);
			//print_array(split2);
		}
		else
			result = ft_split(s, c);
	}
	else
		result = ft_split(s, c);
	//ft_printf("entrou aqui\n");
	//ft_printf("s:%s\n", s);
	//ft_printf("result: %s\n", (const char *)result[0]);
	//print_array(result);
	return(result);
}

/*int	main()
{
	char	**split;
	char	c;
	size_t	i;

	c = ' ';
	split = ft_quotes("awk '{count++} END {print count}'", c);
	//split =
	i = 0;
	while (split[i] != 0)
	{
		printf("%s\n", split[i]);
		i++;
	}
	ft_free_array(&split);
	return (0);
}*/
