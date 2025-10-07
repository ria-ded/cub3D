/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:07:15 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/07 11:52:42 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	validate_format(char *file, char *format)
{
	char	*ext;

	if (!file || !file[0] || !format || !format[0])
		return (-1);
	ext = ft_strrchr(file, '.');
	if (!ext || ft_strncmp(ext, format, ft_strlen(format)) != 0)
	{
		printf("Error: wrong file format\n");
		return (1);
	}
	return (0);
}

int	set_texture(t_config *config, int dir, char *val)
{
	char	*trimmed;

	if (config->tex[dir])
		return (printf("Error: repetitive element\n"), 1);
	trimmed = ft_strtrim(val, " ");
	if (!trimmed)
		return (perror("Error: strtrim\n"), 1);
	if (validate_format(trimmed, ".xpm"))
		return (free(trimmed), 1);
	config->tex[dir] = ft_strdup(trimmed);
	free(trimmed);
	if (!config->tex[dir])
		return (perror("Error: strdup\n"), 1);
	return (0);
}
