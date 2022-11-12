/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkiviloo <rkiviloo@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:56:23 by rkiviloo          #+#    #+#             */
/*   Updated: 2022/11/12 12:47:09 by rkiviloo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*#include <stdio.h>
#include <fcntl.h>*/
char	*init_buf(int fd)
{
	char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	return (buf);
}

int	handle_read(int bytesread, char **buf, char **save)
{
	char	*tmp;

	if (bytesread <= 0 && !*save)
	{
		free(*buf);
		return (0);
	}
	if (bytesread == -1)
	{
		free (*save);
		*save = NULL;
		free (*buf);
		return (0);
	}
	(*buf)[bytesread] = '\0';
	if (!*save)
	{
		tmp = *save;
		*save = ft_strjoin("", "");
		free (tmp);
	}
	return (1);
}

void	handle_read_post(int bytesread, char **output, char **save)
{
	if (bytesread <= 0)
	{
		if (!**save)
		{
			free (*save);
			*save = NULL;
			*output = NULL;
		}
		else
		{
			*output = *save;
			*save = NULL;
		}
	}
}

int	find_line(char **save, char **buf, char **output)
{
	char	*tmp;

	tmp = *save;
	*save = ft_strjoin(*save, *buf);
	free (tmp);
	if (parsesaved(save, output))
	{
		free (*buf);
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*output;
	int			bytesread;
	static char	*save;

	buf = init_buf(fd);
	if (!buf)
		return (NULL);
	bytesread = read(fd, buf, BUFFER_SIZE);
	if (!handle_read(bytesread, &buf, &save))
		return (NULL);
	while (1)
	{
		if (find_line(&save, &buf, &output))
			return (output);
		bytesread = read(fd, buf, BUFFER_SIZE);
		if (bytesread <= 0)
			break ;
		buf[bytesread] = '\0';
	}
	handle_read_post(bytesread, &output, &save);
	free (buf);
	return (output);
}

/*int main(void)
{
	int fd = open("multiple_line_no_nl", O_RDONLY);
	char *a = get_next_line(fd);
	printf("%s", a);
	free (a);
	char *b = get_next_line(fd);
	printf("%s", b);
	free(b);
	char *c = get_next_line(fd);
	printf("%s", c);
	free(c);
	char *d = get_next_line(fd);
	printf("%s", d);
	free(d);
	char *e = get_next_line(fd);
	printf("%s", e);
	free(e);
	char *f = get_next_line(fd);
	printf("%s", f);
	free(f);

	int fd2 = open("only_nl.txt", O_RDONLY);
	char *g = get_next_line(fd2);
	printf("%s", g);
	free(g);
	char *h = get_next_line(fd2);
	printf("%p", h);
	free(h);
	char *i = get_next_line(fd2);
	printf("%p", i);
	free(i);

	return (0);
}*/
