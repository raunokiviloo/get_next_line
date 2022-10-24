/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkiviloo <rkiviloo@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:56:23 by rkiviloo          #+#    #+#             */
/*   Updated: 2022/10/24 19:49:12 by rkiviloo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	if (read(fd, buf, 1) <= 0)
	{
		free(buf);
		return (NULL);
	}
	buf[1] = '\0';
	output = ft_strjoin("", buf);
	return (parseline(buf, buf, fd, output));
}

/*int main(void)
{
	int fd = open("41_no_nl", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	printf("%s", get_next_line(fd));
	int fd2 = open("41_with_nl", O_RDONLY);
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd2));

	return (0);
}*/
