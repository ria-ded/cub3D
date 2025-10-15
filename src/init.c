/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 07:50:51 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/15 11:35:52 by svolkau          ###   ########.fr       */
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
	config->tex[NO] = NULL;
	config->tex[SO] = NULL;
	config->tex[WE] = NULL;
	config->tex[EA] = NULL;
	config->color[CEILING] = -1;
	config->color[FLOOR] = -1;
}

int	init_data(t_data *g, char *file)
{
	ft_bzero(g, sizeof(t_data));
	init_config(&g->config);
	init_player(&g->player);
	if (parse_file(g, file))
		return (1);
	return (0);
}
