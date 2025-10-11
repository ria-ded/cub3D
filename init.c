/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 07:50:51 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/11 11:57:57 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	return (0);
}

int	init_config(t_config *config)
{
	if (!config)
		return (1);
	config->tex[NO] = NULL;
	config->tex[SO] = NULL;
	config->tex[WE] = NULL;
	config->tex[EA] = NULL;
	config->color[CEILING] = -1;
	config->color[FLOOR] = -1;
	return (0);
}

int	init_data(t_data *g, char *av)
{
	ft_bzero(g, sizeof(t_data));
	// g->mlx = mlx_init();
	// if (!g->mlx)
	// 	return (printf("Error: mlx init\n"), 1);
	// g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, file);
	// g->img.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	// g->img.addr = mlx_get_data_addr(
	// 		g->img.img, &g->img.bpp, &g->img.line_len, &g->img.endian);
	g->file = ft_strtrim(av, " ");
	if (!g->file)
		print_err("strtrim", g);
	if (!validate_format(g->file, ".cub"))
		print_err("wrong file format, try .cub", g);
	init_config(&g->config);
	if (parse_file(g))
		return (1);
	init_player(&g->player);
	//init_map(&g->map);
	return (0);
}
