/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkiviloo <rkiviloo@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:32:34 by rkiviloo          #+#    #+#             */
/*   Updated: 2022/10/24 19:46:07 by rkiviloo         ###   ########.fr       */
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

char	*deposit(char *output, char *buf)
{
	char	*to_free;

	to_free = output;
	output = ft_strjoin(output, buf);
	free (to_free);
	return (output);
}

char	*freeandreturn(char *toreturn, char *tofree)
{
	free (tofree);
	return (toreturn);
}

char	*parseline(char *buf, char *obuf, int fd, char *output)
{
	int		bytesread;
	int		bufsize;

	while (*output != '\n')
	{
		bufsize = BUFFER_SIZE;
		buf = obuf;
		while (bufsize--)
		{
			bytesread = read(fd, buf, 1);
			if (bytesread <= 0 || *buf == '\n')
			{
				if (bytesread <= 0)
					*buf = '\0';
				*(buf + 1) = '\0';
				output = deposit(output, obuf);
				return (freeandreturn(output, obuf));
			}
			buf++;
		}
		*buf = '\0';
		output = deposit(output, obuf);
	}
	free(buf);
	return (output);
}
