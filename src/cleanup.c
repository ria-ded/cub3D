/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:43:22 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/16 15:26:52 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	del(char *str)
{
	if (str)
		free(str);
}

void	map_delone(t_map *map, void (*del)(char *))
{
	if (!del)
		return ;
	if (map)
	{
		(*del)(map->str);
		free(map);
	}
}

void	free_map(t_map **map, void (*del)(char *))
{
	t_map	*tmp;

	if (!map || !*map)
		return ;
	while (map && *map)
	{
		tmp = (*map)->next;
		map_delone(*map, del);
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
		free(arr[i++]);
	free(arr);
}

void	free_config(t_config *config)
{
	if (config->tex[NO].path)
		free(config->tex[NO].path);
	if (config->tex[SO].path)
		free(config->tex[SO].path);
	if (config->tex[WE].path)
		free(config->tex[WE].path);
	if (config->tex[EA].path)
		free(config->tex[EA].path);
	if (config->tex[NO].color_arr)
		free(config->tex[NO].color_arr);
	if (config->tex[SO].color_arr)
		free(config->tex[SO].color_arr);
	if (config->tex[WE].color_arr)
		free(config->tex[WE].color_arr);
	if (config->tex[EA].color_arr)
		free(config->tex[EA].color_arr);
}

void	free_data(t_data *g)
{
	if (!g)
		return ;
	free_config(&g->config);
	free_map(&g->map, del);
	free(g->map);
	free_arr(g->gridmap);
	if (g->fd > 0)
		close(g->fd);
	free_gnl_remainder();
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
