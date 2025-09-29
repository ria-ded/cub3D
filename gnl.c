/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:54:48 by mdziadko          #+#    #+#             */
/*   Updated: 2025/09/29 10:11:28 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

void	*grow(void *ptr, int old_len, int new_len)
{
	void	*tmp;

	tmp = malloc(new_len);
	if (!tmp)
		return (NULL);
	if (ptr)
	{
		for (int i = 0; i < old_len; i++)
			((char *)tmp)[i] = ((char *)ptr)[i];
		free (ptr);
	}
	return (tmp);
}

char	*gnl(int fd)
{
	static	char	buf[BUFFER_SIZE];
	static	int		buf_len;
	static	int		buf_pos;
	char			*res;
	int				res_len;

	res = NULL;
	res_len = 0;
	while (1)
	{
		if (buf_pos >= buf_len)
		{
			buf_len = read(fd, buf, BUFFER_SIZE);
			if (buf_len == -1)
				return (perror("Error while reading"), free(res), NULL);
			if (buf_len == 0)
				break ;
			buf_pos = 0;
		}
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


int main()
{
	int		fd = open("test.txt", O_RDONLY);
	char	*line;

	if (!fd)
		return (1);
	while ((line = gnl(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}
