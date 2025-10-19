/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcast_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <svolkau@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:35:52 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/19 20:26:58 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	render(int x, int y, t_data *g, int col)
{
	int	pix;

	pix = (y * g->img.line_len) + (x * (g->img.bpp / 8));
	g->win_data[pix] = col & 0xFF;
	g->win_data[pix + 1] = (col >> 8) & 0xFF;
	g->win_data[pix + 2] = (col >> 16) & 0xFF;
}

void	get_delta_dist(t_data *g)
{
	if (g->ray_dirx == 0)
		g->delta_d_x = 1e30;
	else
		g->delta_d_x = fabs(1 / g->ray_dirx);
	if (g->ray_diry == 0)
		g->delta_d_y = 1e30;
	else
		g->delta_d_y = fabs(1 / g->ray_diry);
}

int	get_texture(t_data *g)
{
	if (g->side == 0)
	{
		if (g->ray_dirx > 0)
			return (EA);
		else
			return (WE);
	}
	else
	{
		if (g->ray_diry > 0)
			return (SO);
		else
			return (NO);
	}
}

void	set_pos(t_data *g)
{
	double	wall_x;

	if (g->side == 0)
		wall_x = g->player.y + g->perp_wall_dist * g->ray_diry;
	else
		wall_x = g->player.x+ g->perp_wall_dist * g->ray_dirx;
	wall_x -= floor(wall_x);
	g->tex_x = (int)(wall_x * (double)g->config.tex[NO].width);
	if (g->side == 0 && g->ray_dirx > 0)
		g->tex_x = g->config.tex[NO].width - g->tex_x - 1;
	if (g->side == 1 && g->ray_dirx < 0)
		g->tex_x = g->config.tex[NO].width - g->tex_x - 1;
}

void	draw_object(t_data *g)
{
	double	step;
	double	tex_pos;
	int		color;
	int		text;

	set_pos(g);
	step = 1.0 * g->config.tex[NO].height / g->line_height;
	tex_pos = (g->draw_start - HEIGHT / 2 + g->line_height / 2) * step;
	while (g->draw_start < g->draw_end)
	{
		g->tex_y = (int)tex_pos & (g->config.tex[NO].height - 1);
		tex_pos += step;
		text = get_texture(g);
		color = g->config.tex[text].color_arr[g->config.tex[text]
			.width * g->tex_y + g->tex_x];
		if (g->side == 1)
			color = (color >> 1) & 8355711;
		render(g->wall_x, g->draw_start, g, color);
		g->draw_start += 1;
	}
	g->wall_x += 1;
}
