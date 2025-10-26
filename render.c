/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:39:53 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/26 22:03:23 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_ray(t_ray *r, t_player *p)
{
	int	axis;

	axis = X;
	while (axis <= Y)
	{
		r->map[axis] = (int)p->pos[axis];
		r->dir[axis] = p->dir[axis] + p->plane[axis] * r->camera_x;
		if (r->dir[axis] == 0.0)
			r->delta_dist[axis] = INFINITY;
		else
			r->delta_dist[axis] = fabs(1.0 / r->dir[axis]);
		if (r->dir[axis] < 0.0)
		{
			r->step[axis] = -1;
			r->side_dist[axis]
				= (p->pos[axis] - r->map[axis]) * r->delta_dist[axis];
		}
		else
		{
			r->step[axis] = 1;
			r->side_dist[axis]
				= (r->map[axis] + 1.0 - p->pos[axis]) * r->delta_dist[axis];
		}
		axis++;
	}
}

bool	hit_wall(t_ray *r, char **map)
{
	while (true)
	{
		if (r->side_dist[X] < r->side_dist[Y])
		{
			r->side_dist[X] += r->delta_dist[X];
			r->map[X] += r->step[X];
			r->side = 0;
		}
		else
		{
			r->side_dist[Y] += r->delta_dist[Y];
			r->map[Y] += r->step[Y];
			r->side = 1;
		}
		if (r->map[Y] < 0 || !map[r->map[Y]] || r->map[X] < 0
			|| r->map[X] >= (int)ft_strlen(map[r->map[Y]]))
			return (false);
		if (map[r->map[Y]][r->map[X]] == '1'
			|| map[r->map[Y]][r->map[X]] == '2')
			return (true);
	}
}

bool	calc_dist(t_ray *r, t_player *p)
{
	if (r->side == 0)
		r->perp_wall_dist
			= (r->map[X] - p->pos[X] + (1 - r->step[X]) / 2.0) / r->dir[X];
	else
		r->perp_wall_dist
			= (r->map[Y] - p->pos[Y] + (1 - r->step[Y]) / 2.0) / r->dir[Y];
	return (r->perp_wall_dist > 0);
}

int	wall_dir(t_ray *r)
{
	int	wall;

	if (r->side == 0)
	{
		if (r->step[X] > 0)
			wall = EA;
		else
			wall = WE;
	}
	else
	{
		if (r->step[Y] > 0)
			wall = SO;
		else
			wall = NO;
	}
	return (wall);
}

int	render(t_data	*g)
{
	int	x;

	clear_frame(g);
	x = 0;
	while (x < WIDTH)
	{
		g->ray.camera_x = 2 * x / (double)WIDTH - 1;
		init_ray(&g->ray, &g->player);
		if (!hit_wall(&g->ray, g->mapa)
			|| !calc_dist(&g->ray, &g->player))
		{
			x++;
			continue ;
		}
		draw_line(g, wall_dir(&g->ray), x);
		x++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	return (0);
}
