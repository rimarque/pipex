/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:53:06 by rimarque          #+#    #+#             */
/*   Updated: 2023/05/16 19:48:20 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**ft_splitjoin(char *temp, char *temp2, const char *s, char c)
{
	char	*str_in_quotes;
	char	*str1;
	char	*str2;
	char	**split1;
	char	**split2;

	str_in_quotes = ft_substr(temp, 1, ft_strclen(temp + 1, 39));
	str1 = ft_substr(s, 0, ft_strclen(s, 39));
	split1 = ft_split(str1, c);
	str2 = ft_substr(temp2, 1, ft_strclen(temp + 1, 39));
	split2 = ft_split(str2, c);
	return (ft_arrjoin(split1, str_in_quotes, split2));
}

char	**ft_quotes(char const *s, char c)
{
	char	*temp;
	char	*temp2;
	char	**result;

	result = NULL;
	temp = ft_strchr(s, 39);
	if (temp)
	{
		temp2 = ft_strchr(temp + 1, 39);
		if (temp2)
		{
			if (temp && *(temp - 1) == c
				&& (*(temp2 + 1) == c || *(temp2 + 1) == '\0'))
				result = ft_splitjoin(temp, temp2, s, c);
		}
	}
	if (!result)
		result = ft_split(s, c);
	return (result);
}
