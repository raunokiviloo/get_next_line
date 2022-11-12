/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkiviloo <rkiviloo@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:32:34 by rkiviloo          #+#    #+#             */
/*   Updated: 2022/11/12 10:11:50 by rkiviloo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstring;
	char	*newstring_index;

	if (!s1 || !s2)
		return (NULL);
	newstring = malloc(sizeof(*newstring)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstring)
		return (NULL);
	newstring_index = newstring;
	while (*s1)
		*newstring_index++ = *s1++;
	while (*s2)
		*newstring_index++ = *s2++;
	*newstring_index = '\0';
	return (newstring);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	char	*substring_index;
	size_t	substring_len;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		substring = malloc(sizeof(*substring));
		*substring = '\0';
		return (substring);
	}
	substring_len = ft_strlen(s) - start;
	if (len < substring_len)
		substring_len = len;
	substring = malloc(sizeof(*substring) * (substring_len + 1));
	if (!substring)
		return (NULL);
	substring_index = substring;
	while (len-- > 0 && s[start])
		*substring_index++ = s[start++];
	*substring_index = '\0';
	return (substring);
}

int	parsesaved(char **save, char **output)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while ((*save)[i])
	{
		if ((*save)[i] == '\n')
		{
			*output = ft_substr(*save, 0, i + 1);
			tmp = *save;
			*save = ft_substr(*save, i + 1, (size_t) - 1);
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}
