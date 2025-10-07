/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:43:22 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/07 18:22:07 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	del(char *str)
{
	if (str)
		free(str);
}

void	mapdelone(t_map *map, void (*del)(char *))
{
	if (!del)
		return ;
	if (map)
	{
		(*del)(map->str);
		free(map);
	}
}

void	freemap(t_map **map, void (*del)(char *))
{
	t_map	*tmp;

	if (!map || !*map)
		return ;
	while (map && *map)
	{
		tmp = (*map)->next;
		mapdelone(*map, del);
		*map = tmp;
	}
	*map = NULL;
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_config(t_config *config)
{
	if (config->tex[NO])
		free(config->tex[NO]);
	if (config->tex[SO])
		free(config->tex[SO]);
	if (config->tex[WE])
		free(config->tex[WE]);
	if (config->tex[EA])
		free(config->tex[EA]);
}

void	free_data(t_data *g)
{
	if (!g)
		return ;
	free_config(&g->config);
	freemap(&g->map, del);
	free(g->map);
	/* if (g->mlx && g->img.img)
	{
		mlx_destroy_image(g->mlx, g->img.img);
		g->img.img = NULL;
	}
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
# ifdef __linux__
	mlx_destroy_display(g->mlx);
	free (g->mlx);
# endif */
}
