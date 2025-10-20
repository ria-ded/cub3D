/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:07:15 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/20 12:45:05 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	validate_format(char *file, char *format)
{
	char	*ext;

	if (!file || !file[0] || !format || !format[0])
		return (-1);
	ext = ft_strrchr(file, '.');
	if (!ext || ft_strncmp(ext, format, ft_strlen(format)) != 0
		|| ext[ft_strlen(format)] != '\0')
		return (printf("Error: wrong file format %s\n", ext), 1);
	return (0);
}

int	set_texture(t_config *config, int dir, char *val)
{
	char	*trimmed;
	int		fd;

	if (config->tex[dir].path)
		return (printf("Error: repetitive element\n"), 1);
	trimmed = ft_strtrim(val, " \n");
	if (!trimmed)
		return (perror("Error: strtrim\n"), 1);
	if (validate_format(trimmed, ".ppm"))
		return (free(trimmed), 1);
	else
	{
		fd = open(trimmed, O_RDONLY);
		if (fd == -1)
			return (free(trimmed), perror("Error: open file texture "),
				close(fd), 1);
		close(fd);
	}
	config->tex[dir].path = ft_strdup(trimmed);
	free(trimmed);
	if (!config->tex[dir].path)
		return (perror("Error: strdup\n"), 1);
	return (0);
}
