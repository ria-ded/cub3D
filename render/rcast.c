/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:55:37 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/21 13:53:57 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw(t_data *g)
{
	g->line_height = (int)(HEIGHT / g->perp_wall_dist);
	g->draw_start = -g->line_height / 2 + HEIGHT / 2;
	if (g->draw_start < 0)
		g->draw_start = 0;
	g->draw_end = g->line_height / 2 + HEIGHT / 2;
	if (g->draw_end > HEIGHT)
		g->draw_end = HEIGHT - 1;
	draw_object(g);
}

void	distance(t_data *g)
{
	if (g->side == 0)
		g->perp_wall_dist = g->side_d_x - g->delta_d_x;
	else
		g->perp_wall_dist = g->side_d_y - g->delta_d_y;
	draw(g);
}

void	move_ray(t_data *g)
{
	while (g->hit == 0)
	{
		if (g->side_d_x < g->side_d_y)
		{
			g->side_d_x += g->delta_d_x;
			g->map_x += g->step_x;
			g->side = 0;
		}
		else
		{
			g->side_d_y += g->delta_d_y;
			g->map_y += g->step_y;
			g->side = 1;
		}
		if ((int)g->gridmap[g->map_y][g->map_x] - 48 == 1)
			g->hit = 1;
	}
	distance(g);
}

void	set_ray(t_data *g)
{
	g->map_x = (int)g->player.x;
	g->map_y = (int)g->player.y;
	g->hit = 0;
	get_delta_dist(g);
	if (g->ray_dirx < 0)
	{
		g->step_x = -1;
		g->side_d_x = (g->player.x - g->map_x) * g->delta_d_x;
	}
	else
	{
		g->step_x = 1;
		g->side_d_x = (g->map_x + 1.0 - g->player.x) * g->delta_d_x;
	}
	if (g->ray_diry < 0)
	{
		g->step_y = -1;
		g->side_d_y = (g->player.y - g->map_y) * g->delta_d_y;
	}
	else
	{
		g->step_y = 1;
		g->side_d_y = (g->map_y + 1.0 - g->player.y) * g->delta_d_y;
	}
	move_ray(g);
}

void	cast_rays(t_data *g)
{
	int	x;

	x = -1;
	g->tex_x = 0;
	g->tex_y = 0;
	g->wall_x = 0;
	while (++x < WIDTH)
	{
		g->camera_x = 2 * x / (double)WIDTH - 1;
		g->ray_dirx = g->dir_x + g->plane_x * g->camera_x;
		g->ray_diry = g->dir_y + g->plane_y * g->camera_x;
		set_ray(g);
	}
}
