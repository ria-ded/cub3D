/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:39:53 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/09 14:49:17 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void start_game(t_data *cb3d)
{
	cb3d->mlx = mlx_init();
	if (!cb3d->mlx)
		free_data(cb3d);
	cb3d->win = mlx_new_window(cb3d->mlx, WIDTH, HEIGHT, "CUB3D");
	cb3d->img = mlx_new_image(cb3d->mlx, WIDTH, HEIGHT);
	cb3d->img->addr = mlx_get_data_addr(cb3d->img, &cb3d->img->bpp, &cb3d->img->line_len, &cb3d->img->endian);
}
