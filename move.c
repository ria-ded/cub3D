/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:56:18 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/26 22:03:23 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_forward(t_data *g)
{
	if ((int)g->mapa[(int)(g->player.pos[Y])]
			[(int)(g->player.pos[X] + g->player.dir[X] * 0.15)] - 48 != 1)
		g->player.pos[X] += g->player.dir[X] * 0.15;
	if ((int)g->mapa[(int)(g->player.pos[Y] + g->player.dir[Y] * 0.15)]
			[(int)(g->player.pos[X])] - 48 != 1)
		g->player.pos[Y] += g->player.dir[Y] * 0.15;
}

void	move_backward(t_data *g)
{
	if ((int)g->mapa[(int)(g->player.pos[Y])]
			[(int)(g->player.pos[X] - g->player.dir[X] * 0.15)] - 48 != 1)
		g->player.pos[X] -= g->player.dir[X] * 0.15;
	if ((int)g->mapa[(int)(g->player.pos[Y] - g->player.dir[Y] * 0.15)]
			[(int)(g->player.pos[X])] - 48 != 1)
		g->player.pos[Y] -= g->player.dir[Y] * 0.15;
}

void	move_right(t_data *g)
{
	float	dir_x;
	float	dir_y;

	dir_x = g->player.dir[Y];
	dir_y = -g->player.dir[X];
	if ((int)g->mapa[(int)(g->player.pos[Y])]
			[(int)(g->player.pos[X] + dir_x * 0.15)] - 48 != 1)
		g->player.pos[X] += dir_x * 0.15;
	if ((int)g->mapa[(int)(g->player.pos[Y] + dir_y * 0.15)]
			[(int)(g->player.pos[X])] - 48 != 1)
		g->player.pos[Y] += dir_y * 0.15;
}

void	move_left(t_data *g)
{
	float	dir_x;
	float	dir_y;

	dir_x = g->player.dir[Y];
	dir_y = -g->player.dir[X];
	if ((int)g->mapa[(int)(g->player.pos[Y])]
			[(int)(g->player.pos[X] - dir_x * 0.15)] - 48 != 1)
		g->player.pos[X] -= dir_x * 0.15;
	if ((int)g->mapa[(int)(g->player.pos[Y] - dir_y * 0.15)]
			[(int)(g->player.pos[X])] - 48 != 1)
		g->player.pos[Y] -= dir_y * 0.15;
}
