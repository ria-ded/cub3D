/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:07:15 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/22 01:02:04 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	validate_format(char *file, char *format)
{
	char	*ext;

	if (!file || !file[0] || !format || !format[0])
		return (false);
	ext = ft_strrchr(file, '.');
	if (!ext || ft_strncmp(ext, format, ft_strlen(format)) != 0
		|| ext[ft_strlen(format)] != '\0')
		return (false);
	return (true);
}

int	set_texture(t_data *g, int dir, char *val)
{
	char	*trimmed;
	int		fd;

	if (g->c.tex_path[dir])
		return (printf("Error\nRepetitive element\n"), 1);
	trimmed = ft_strtrim(val, " \n");
	if (!trimmed)
		return (printf("Error\nStrtrim\n"), 1);
	if (!validate_format(trimmed, ".ppm") && !validate_format(trimmed, ".xpm"))
		return (printf("Error\nWrong file format, try .ppm or .xpm\n"),
			free(trimmed), 1);
	fd = open(trimmed, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nOpen file texture\n"), free(trimmed), 1);
	g->c.tex_path[dir] = ft_strdup(trimmed);
	free(trimmed);
	if (!g->c.tex_path[dir])
		return (printf("Error\nStrdup\n"), close(fd), 1);
	if (texture_loading(g, dir))
		return (close(fd), 1);
	close(fd);
	return (0);
}

int	texture_loading(t_data *g, int dir)
{
	g->c.tex[dir].img = mlx_xpm_file_to_image(
		g->mlx, g->c.tex_path[dir],
		&g->c.tex[dir].width,
		&g->c.tex[dir].height);
	if (!g->c.tex[dir].img)
		return (printf("Error\nTexture loading\n"), 1);
	g->c.tex[dir].addr = mlx_get_data_addr(
		g->c.tex[dir].img,
		&g->c.tex[dir].bpp,
		&g->c.tex[dir].line_len,
		&g->c.tex[dir].endian);
	return (0);
}
