/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 08:21:35 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/22 01:01:20 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_line(t_data *g, int dir, int screen_x)
{
	double	offset;
	double	tex[2];

	g->ray.line_height = HEIGHT / g->ray.perp_wall_dist;
	g->ray.draw_start = -g->ray.line_height / 2 + HEIGHT / 2;
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;
	g->ray.draw_end = g->ray.line_height / 2 + HEIGHT / 2;
	if (g->ray.draw_end >= HEIGHT)
		g->ray.draw_end = HEIGHT - 1;
	if (g->ray.side == 0)
		offset = g->player.pos[Y] + g->ray.perp_wall_dist * g->ray.dir[Y];
	else
		offset = g->player.pos[X] + g->ray.perp_wall_dist * g->ray.dir[X];
	offset -= floor(offset);
	tex[X] = (int)(offset * g->c.tex[dir].width);
	if ((g->ray.side == 0 && g->ray.dir[X] > 0)
		|| (g->ray.side == 1 && g->ray.dir[Y] < 0))
		tex[X] = g->c.tex[dir].width - tex[X] - 1;
	tex[Y] = (g->ray.draw_start - HEIGHT / 2.0 + g->ray.line_height / 2.0)
		* ((double)g->c.tex[dir].height / (double)g->ray.line_height);
	put_texture(g, tex, dir, screen_x);
}

void	put_texture(t_data *g, double tex[2], int dir, int x)
{
	int				y;
	unsigned int	color;
	double			step;

	y = g->ray.draw_start;
	step = (double)g->c.tex[dir].height / (double)g->ray.line_height;
	while (y <= g->ray.draw_end)
	{
		if (tex[Y] < 0)
			tex[Y] = 0;
		else if (tex[Y] >= g->c.tex[dir].height)
			tex[Y] = g->c.tex[dir].height - 1;
		color = *(unsigned int *)(g->c.tex[dir].addr
				+ (int)tex[Y] * g->c.tex[dir].line_len
				+ (int)tex[X] * (g->c.tex[dir].bpp / 8));
		if (g->ray.side == 1)
			color = (color & 0xFEFEFE) >> 1;
		pixel_put(g, x, y, color);
		tex[Y] += step;
		y++;
	}
}

void	pixel_put(t_data *g, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = g->img.addr + (y * g->img.line_len + x * (g->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear_frame(t_data *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				pixel_put(g, x, y, g->c.color[CEILING]);
			else
				pixel_put(g, x, y, g->c.color[FLOOR]);
			x++;
		}
		y++;
	}
}
