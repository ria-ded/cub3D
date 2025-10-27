/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 21:53:00 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/26 21:58:48 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	close_win(t_data *g)
{
	if (g->has_exited)
		return (0);
	g->has_exited = 1;
	free_data(g);
	exit (EXIT_SUCCESS);
}

int	handle_keys(int keycode, t_data *g)
{
	if (keycode == KEY_ESC)
		close_win(g);
	if (keycode == KEY_W)
		move_forward(g);
	if (keycode == KEY_S)
		move_backward(g);
	if (keycode == KEY_A)
		move_left(g);
	if (keycode == KEY_D)
		move_right(g);
	if (keycode == KEY_LEFT)
		turn_left(g);
	if (keycode == KEY_RIGHT)
		turn_right(g);
	render(g);
	return (0);
}

void	handle_events(t_data *g)
{
	mlx_hook(g->win, 17, 0, close_win, g);
	mlx_hook(g->win, 2, 1L << 0, handle_keys, g);
	mlx_loop(g->mlx);
}
