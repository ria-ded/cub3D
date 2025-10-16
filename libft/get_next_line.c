/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:41:35 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/16 15:26:58 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* file-scoped remainder so it can be freed by free_gnl_remainder() */
static char *remainder = NULL;

int	read_and_store(int fd, char **remainder)
{
	char	*buf;
	int		bytes_read;
	char	*temp;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	while (!ft_strchr(*remainder, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read < 0)
			return (free(buf), -1);
		buf[bytes_read] = '\0';
		temp = ft_strjoin(*remainder, buf);
		if (!temp)
			return (free(buf), -1);
		free(*remainder);
		*remainder = temp;
	}
	return (free(buf), 0);
}

void	extract_line(char **remainder, char **line)
{
	char	*new_line;
	char	*temp;
	size_t	len;

	new_line = ft_strchr(*remainder, '\n');
	if (new_line)
	{
		len = new_line - (*remainder) + 1;
		*line = ft_substr(*remainder, 0, len);
		temp = ft_strdup(new_line + 1);
	}
	else
	{
		*line = ft_strdup(*remainder);
		temp = NULL;
	}
	free(*remainder);
	*remainder = temp;
}

char	*get_next_line(int fd)
{
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	if (!remainder)
		return (NULL);
	if (read_and_store(fd, &remainder) == -1)
		return (free(remainder), NULL);
	if (!remainder || !(*remainder))
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	extract_line(&remainder, &line);
	return (line);
}

void	free_gnl_remainder(void)
{
	if (remainder)
	{
		free(remainder);
		remainder = NULL;
	}
}

/*
static void	*grow(void *ptr, int old_len, int new_len)
{
	void	*tmp;
	int		i;

	tmp = malloc(new_len * sizeof(char));
	if (!tmp)
		return (NULL);
	if (ptr)
	{
		i = 0;
		while (i < old_len)
		{
			((char *)tmp)[i] = ((char *)ptr)[i];
			i++;
		}
		free (ptr);
	}
	return (tmp);
}

static int	fill_buf(int fd, char *buf, int *buf_len, int *buf_pos)
{
	*buf_len = read(fd, buf, BUFFER_SIZE);
	if (*buf_len == -1)
		return (perror("Error while reading from file"), -1);
	*buf_pos = 0;
	return (*buf_len);
}

char	*gnl(int fd)
{
	static char	buf[BUFFER_SIZE];
	static int	buf_len;
	static int	buf_pos;
	char		*res;
	int			res_len;

	res = NULL;
	res_len = 0;
	while (1)
	{
		if (buf_pos >= buf_len && !fill_buf(fd, buf, &buf_len, &buf_pos))
			break ;
		if (buf_len == -1)
			return (free(res), NULL);
		res = grow(res, res_len, res_len + 2);
		if (!res)
			return (NULL);
		res[res_len++] = buf[buf_pos++];
		res[res_len] = '\0';
		if (res[res_len - 1] == '\n')
			break ;
	}
	if (!res_len)
		return (free(res), NULL);
	return (res);
}

// int main()
// {
// 	int		fd = open("test.txt", O_RDONLY);
// 	char	*line;

// 	if (fd == -1)
// 		return (1);
// 	while ((line = gnl(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// }

*/