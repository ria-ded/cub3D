/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 00:43:44 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/26 22:03:23 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	setup_game(t_data *g)
{
	g->mapa = map_to_arr(g->map);
	if (!g->mapa)
		print_err("Map to arr", g);
	g->player.pos[X] = (double)g->player.x + 0.5;
	g->player.pos[Y] = (double)g->player.y + 0.5;
	set_dir(&g->player);
	set_plane(&g->player);
	load_texture(g);
}

void	load_texture(t_data *g)
{
	int	dir;

	dir = 0;
	while (dir < 4)
	{
		g->c.tex[dir].img = mlx_xpm_file_to_image(
				g->mlx, g->c.tex_path[dir],
				&g->c.tex[dir].width,
				&g->c.tex[dir].height);
		if (!g->c.tex[dir].img)
			print_err(("Texture loading"), g);
		g->c.tex[dir].addr = mlx_get_data_addr(
				g->c.tex[dir].img,
				&g->c.tex[dir].bpp,
				&g->c.tex[dir].line_len,
				&g->c.tex[dir].endian);
		if (!g->c.tex[dir].addr)
			print_err(("Texture data addr"), g);
		dir++;
	}
}

void	set_plane(t_player *p)
{
	double	plane_length;

	plane_length = tan((FOV * M_PI / 180.0) / 2.0);
	p->plane[X] = p->dir[Y] * plane_length;
	p->plane[Y] = -p->dir[X] * plane_length;
}

void	set_dir(t_player *p)
{
	if (p->orient == 'S')
	{
		p->dir[X] = 0;
		p->dir[Y] = 1;
	}
	else if (p->orient == 'N')
	{
		p->dir[X] = 0;
		p->dir[Y] = -1;
	}
	else if (p->orient == 'W')
	{
		p->dir[X] = -1;
		p->dir[Y] = 0;
	}
	else if (p->orient == 'E')
	{
		p->dir[X] = 1;
		p->dir[Y] = 0;
	}
}
