/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 07:50:51 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/16 14:33:51 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
}

void	init_config(t_config *config)
{
	config->tex[NO].path = NULL;
	config->tex[NO].color_arr = NULL;
	config->tex[NO].type = "NO";
	config->tex[SO].path = NULL;
	config->tex[SO].color_arr = NULL;
	config->tex[SO].type = "SO";
	config->tex[WE].path = NULL;
	config->tex[WE].color_arr = NULL;
	config->tex[WE].type = "WE";
	config->tex[EA].path = NULL;
	config->tex[EA].color_arr = NULL;
	config->tex[EA].type = "EA";
	config->color[CEILING] = -1;
	config->color[FLOOR] = -1;
}

void	init_main_data(t_data *g)
{
	g->fd = 0;
	g->mlx = NULL;
	g->img = NULL;
	g->win = NULL;
	g->map = NULL;
	g->gridmap = NULL;
}

void init_color_arrs(t_data *g)
{
	add_color_arr(g, NO);
	add_color_arr(g, SO);
	add_color_arr(g, WE);
	add_color_arr(g, EA);
}

int	init_data(t_data *g, char *file)
{
	ft_bzero(g, sizeof(t_data));
	init_config(&g->config);
	init_player(&g->player);
	init_main_data(g);
	if (parse_file(g, file))
		return (1);
	init_color_arrs(g);
	return (0);
}
