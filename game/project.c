/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:51:23 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/21 14:04:34 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	closewin(t_data *g)
{
	if (g && g->mlx)
		mlx_loop_end(g->mlx);
	return (0);
}

int	handlevent(int keycode, t_data *g)
{
	if (keycode == KEY_ESC)
		closewin(g);
	return (0);
}

void	start_game(t_data *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		free_data(g);
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "CUB3D");
	g->img.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->win_data = mlx_get_data_addr(g->img.img, &g->img.bpp,
			&g->img.line_len, &g->img.endian);
	set_orient(g);
	print_display(g);
	mlx_hook(g->win, 17, 0, closewin, g);
	mlx_key_hook(g->win, handlevent, g);
	mlx_loop(g->mlx);
}
