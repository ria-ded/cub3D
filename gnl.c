/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:54:48 by mdziadko          #+#    #+#             */
/*   Updated: 2025/09/29 23:20:35 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
