/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:53:31 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/22 16:51:00 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	closewin(t_data *g)
{
	if (g && g->mlx)
		mlx_loop_end(g->mlx);
	return (0);
}

static int	handlevent(int keycode, t_data *g)
{
	if (keycode == KEY_ESC)
		closewin(g);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	g;

	if (argc != 2)
		return (printf("Error\nwrong number of arguments\n"), 1);
	if ((argv[1][0] == '.' && argv[1][1] == '.'))
		return (printf("Error\nrelative path\n"), 1);
	if (init_data(&g, argv[1]))
		return (1);
	render(&g);
	mlx_hook(g.win, 17, 0, &closewin, &g);
	mlx_hook(g.win, KeyPress, KeyPressMask, &handlevent, &g);
	mlx_loop(g.mlx);
	free_data(&g);
	return (0);
}
