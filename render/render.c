/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:39:53 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/21 13:44:00 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	set_orient_values(t_data *g, double x, double y, double px, double py)
{
	g->dir_x = x;
	g->dir_y = y;
	g->plane_x = px;
	g->plane_y = py;
}

void	set_orient(t_data *g)
{
	if (g->player.orient == 'N')
		set_orient_values(g, 0, -1, 0.66, 0);
	else if (g->player.orient == 'S')
		set_orient_values(g, 0, 1, -0.66, 0);
	else if (g->player.orient == 'E')
		set_orient_values(g, 1, 0, 0, 0.66);
	else if (g->player.orient == 'W')
		set_orient_values(g, -1, 0, 0, -0.66);
}

void	set_pixel(t_data *g, int x, int y, int color)
{
	int	pix;

	pix = (y * g->img.line_len) + (x * (g->img.bpp / 8));
	g->win_data[pix] = color & 0xFF;
	g->win_data[pix + 1] = (color >> 8) & 0xFF;
	g->win_data[pix + 2] = (color >> 16) & 0xFF;
	if (g->img.bpp == 32)
		g->win_data[pix + 3] = 0x00;
}

void	draw_cf(t_data *g, char flag)
{
	int	x;
	int	y;
	int	color;
	int	size;

	if (flag == 'f')
	{
		y = -1;
		size = HEIGHT / 2;
		color = g->config.color[CEILING];
	}
	if (flag == 'c')
	{
		y = (HEIGHT / 2) - 1;
		size = HEIGHT;
		color = g->config.color[FLOOR];
	}
	while (++y < size)
	{
		x = -1;
		while (++x < WIDTH)
			set_pixel(g, x, y, color);
	}
}

void	print_display(t_data *g)
{
	mlx_destroy_image(g->mlx, g->img.img);
	g->img.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->win_data = mlx_get_data_addr(g->img.img, &g->img.bpp,
			&g->img.line_len, &g->img.endian);
	draw_cf(g, 'f');
	draw_cf(g, 'c');
	cast_rays(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
}
